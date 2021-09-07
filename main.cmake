#设置工程名
set(PROJECT_NAME W600Demo)

#设置源文件
list(APPEND MAIN_SRCS
main.c
cpp.cpp
cpp.c
wifinetwork.c
)

#设置头文件
list(APPEND MAIN_INCLUDE_DIRS
./
)
