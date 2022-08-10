

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ADDR2LINE arm-none-eabi-addr2line)
set(CMAKE_AR arm-none-eabi-ar)
set(CMAKE_RANLIB arm-none-eabi-ranlib)
set(CMAKE_CXX_COMPILER_AR arm-none-eabi-ar)
set(CMAKE_CXX_COMPILER_RANLIB arm-none-eabi-ranlib)
set(CMAKE_C_COMPILER_AR arm-none-eabi-ar)
set(CMAKE_C_COMPILER_RANLIB arm-none-eabi-ranlib)
set(CMAKE_Fortran_COMPILER arm-none-eabi-gfortan)
set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(CMAKE_RC_COMPILER arm-none-eabi-windres)
set(CMAKE_READELF arm-none-eabi-readelf)
set(CMAKE_STRIP arm-none-eabi-strip)
set(CMAKE_LINKER arm-none-eabi-ld)

set(CMAKE_EXECUTABLE_SUFFIX_ASM .elf)
set(CMAKE_EXECUTABLE_SUFFIX_C .elf)
set(CMAKE_EXECUTABLE_SUFFIX_CXX .elf)

execute_process(COMMAND ${CMAKE_C_COMPILER}  -dumpversion OUTPUT_VARIABLE gcc_version OUTPUT_STRIP_TRAILING_WHITESPACE)

set(CMAKE_C_COMPILER_FORCED TRUE)
set(CMAKE_CXX_COMPILER_FORCED TRUE)
