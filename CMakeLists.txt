
cmake_minimum_required(VERSION 3.10)

include(${CMAKE_CURRENT_SOURCE_DIR}/main.cmake)

if(NOT DEFINED PROJECT_NAME)
	set(PROJECT_NAME w600)
endif()

#设置编译工具链及选项
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/toolchain.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/option.cmake)

project(${PROJECT_NAME} C CXX ASM)


#设置SDK所在目录
set(SDK_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/WM_SDK_60X)

#包含SDK相关cmake（提供变量SDK_INCLUDE_DIRS(头文件目录) SDK_PRECOMPILED_LIBS(库列表)）
include(${CMAKE_SOURCE_DIR}/cmake/sdk/common.cmake)



if(NOT DEFINED MAIN_SRCS)
	set(MAIN_SRCS ${SDK_ROOT}/App/main.c )
endif()

list(APPEND MAIN_SRCS

#Boot
${SDK_ROOT}/Platform/Boot/gcc/startup_ARMCM3.S
${SDK_ROOT}/Platform/Boot/gcc/misc.c
${SDK_ROOT}/Platform/Boot/gcc/retarget_gcc.c

)

if(NOT DEFINED MAIN_INCLUDE_DIRS)
	set(MAIN_INCLUDE_DIRS ./)
endif()



#Kconfig(使用Kconfig进行配置)
option(USE_KCONFIG "use kconfig" ON)

if(${USE_KCONFIG})

    add_definitions(" -DUSE_KCONFIG=1 ")

    find_program(PYTHON
               NAMES python3 python python2
               REQUIRED
               )
    message("python path: ${PYTHON}")
    #安装依赖
    execute_process(COMMAND ${PYTHON} -m pip install -r  ${CMAKE_CURRENT_SOURCE_DIR}/requirement.txt
                      RESULT_VARIABLE PYTHON_INSTALL_RESULT)
    if(PYTHON_INSTALL_RESULT EQUAL 0)
    message("install from requirement.txt success")
    else()
    message(FATAL_ERROR "install from requirement.txt error")
    endif()

    #生成config.h
    add_custom_command(OUTPUT config.h
                    COMMAND ${PYTHON} -m genconfig --header-path config.h
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    )


    if(CMAKE_HOST_WIN32)
        #menuconfig 目标(windows)
        add_custom_target(menuconfig cmd.exe /C start cmd.exe /c ${PYTHON} -m menuconfig
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                  USES_TERMINAL
                  )
    else()
        #menuconfig 目标(非windows)
        add_custom_target(menuconfig  ${PYTHON} -m menuconfig
                  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                  USES_TERMINAL
                  )
    endif()

    #将config.h添加至MAIN_SRCS
    list(APPEND MAIN_SRCS
         config.h )


endif()

#添加资源目录
add_subdirectory(rc)
list(APPEND LIBS
RC
)

#添加SimpleMQTTGateWayStack库
add_subdirectory(lib/SimpleMQTTGateWayStack/lib)

#添加MQTT移植
file(GLOB  PAHO_PORT_C_FILES lib/MQTT/*.c)
list(APPEND PAHO_SRCS
${PAHO_MQTTPACKET_C_FILES}
${PAHO_PORT_C_FILES}
)
add_library(PAHO_MQTT STATIC ${PAHO_SRCS})
target_include_directories(PAHO_MQTT
PUBLIC lib/MQTT/
PRIVATE ${SDK_INCLUDE_DIRS}
)
target_compile_definitions(PAHO_MQTT
PUBLIC MQTTCLIENT_PLATFORM_HEADER=MQTTFreeRTOS_LWIP.h MQTT_TASK
)
target_link_libraries(PAHO_MQTT SMGS)

list(APPEND LIBS
PAHO_MQTT
)

#设置头文件
include_directories(${MAIN_INCLUDE_DIRS})

#添加可执行文件
add_executable(${PROJECT_NAME} ${MAIN_SRCS})
target_link_libraries(${PROJECT_NAME} ${LIBS} ${SDK_PRECOMPILED_LIBS} )

#生成bin文件
add_custom_target(${PROJECT_NAME}.bin ALL
				 COMMAND ${CMAKE_OBJCOPY} --output-target=binary -S -g -x -X ${PROJECT_NAME}.elf ${PROJECT_NAME}.bin
				 DEPENDS ${PROJECT_NAME}
				 )

#准备wm_tool
find_program(WM_TOOL
               NAMES wm_tool
               PATHS ${SDK_ROOT}/Tools ${CMAKE_BINARY_DIR}/
               NO_CACHE
               )
if(NOT EXISTS ${WM_TOOL})
    message("wm_tool is not found,try to compile!")
    #使用C编译器编译
    find_program(CC NAMES cc gcc REQUIRED)
    message("cc path: ${CC}")
    execute_process(COMMAND ${CC} -pthread ${SDK_ROOT}/Tools/src/wm_tool.c  -o ${CMAKE_BINARY_DIR}/wm_tool)
    find_program(WM_TOOL
               NAMES wm_tool
               PATHS  ${CMAKE_BINARY_DIR}/ ${SDK_ROOT}/Tools
               NO_CACHE
               REQUIRED
               )
    message("wm_tool path: ${WM_TOOL}" )
else()
    message("wm_tool path: ${WM_TOOL}" )
endif()

if(${BUILD_FLASH_2M})
    set(GREATE_IMG_FLAGS  -b ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.bin -sb ${SDK_ROOT}/Bin/secboot.img  -fc compress -it 2M -ua 100000 -ra 10100 -df -o ${PROJECT_NAME})
else()
    set(GREATE_IMG_FLAGS  -b ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.bin -sb ${SDK_ROOT}/Bin/secboot.img  -fc compress -it 1M -ua 90000 -ra 10100 -df -o ${PROJECT_NAME})
endif()

#生成其它镜像文件（包括fls文件）
add_custom_target(${PROJECT_NAME}.fls ALL
				 COMMAND ${WM_TOOL} ${GREATE_IMG_FLAGS}
				 DEPENDS ${PROJECT_NAME}.bin
				 )

#flash 目标 （使用 make flash WM_PORT=串口 烧录）

##默认的烧录串口
##环境变量
if(NOT DEFINED ENV{WM_PORT})
    set(ENV{WM_PORT} ttyUSB0)
endif()


add_custom_target(flash
                    COMMAND ${WM_TOOL} -c $ENV{WM_PORT} -eo all -dl ${PROJECT_NAME}.fls
                    DEPENDS ${PROJECT_NAME}.fls
                    )



#run目标
add_custom_target(run
                   COMMAND ${WM_TOOL} -c $ENV{WM_PORT} -eo all -dl ${PROJECT_NAME}.fls -sl str -ws 115200
                   DEPENDS ${PROJECT_NAME}.fls
                  )

