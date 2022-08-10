#设置工程名
set(PROJECT_NAME W600Demo)

file(GLOB MAIN_C_CPP_FILES *.c *.cpp *.h appstack/*.h appstack/*.cpp  appstack/*.c)
#设置源文件
list(APPEND MAIN_SRCS
${MAIN_C_CPP_FILES}
)

#设置头文件
list(APPEND MAIN_INCLUDE_DIRS
./
appstack
)
