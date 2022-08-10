

set(CMAKE_C_FLAGS " ${CMAKE_C_FLAGS} \
		-Wall \
		-DGCC_COMPILE=1 \
		-Os \
		--function-sections \
		--data-sections \
		-mcpu=cortex-m3 \
		-std=gnu2x \
		-march=armv7-m \
		 ")
set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} \
                -Wall \
                -DGCC_COMPILE=1 \
                -Os \
                --function-sections \
                --data-sections \
                -mcpu=cortex-m3 \
                -std=c++2a \
                -march=armv7-m \
                 " )


set(CMAKE_EXE_LINKER_FLAGS " ${CMAKE_EXE_LINKER_FLAGS}\
		-static	\
		-static-libgcc	\
		-static-libstdc++	\
		-Wl,--gc-sections \
		-mcpu=cortex-m3 ")


set(BUILD_SHARED_LIBS OFF)

