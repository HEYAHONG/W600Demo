

set(CMAKE_C_FLAGS " ${CMAKE_C_FLAGS} \
		-Wall \
		-DGCC_COMPILE=1 \
		-mthumb \
		-Os \
		--function-sections \
		--data-sections \
		-mcpu=cortex-m3 \
		-std=gnu99 \
		-march=armv7-m \
		-mabi=aapcs \
		-fno-builtin	\
		 ")
set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} \
                -Wall \
                -DGCC_COMPILE=1 \
                -mthumb \
                -Os \
                --function-sections \
                --data-sections \
                -mcpu=cortex-m3 \
                -std=c++11 \
                -march=armv7-m \
                -mabi=aapcs \
                -fno-builtin    \
                 " )


set(CMAKE_EXE_LINKER_FLAGS " ${CMAKE_EXE_LINKER_FLAGS}\
		-static	\
		-nostartfiles	\
		-mthumb	\
		-mcpu=cortex-m3 ")


set(BUILD_SHARED_LIBS OFF)

