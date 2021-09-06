# 说明

这是一个使用[W600](https://www.winnermicro.com/html/1/156/158/497.html)开发的Demo（仅供测试）。

# 编译

## 工具

- gcc:用于编译wm_tool,windows平台不需要。
- arm-none-eabi-gcc :工具链，C运行库为newlib，windows平台下需使用MSYS2/Cygwin下的arm-none-eabi-gcc。
- cmake :生成工程文件。
- make ：执行编译，也可使用其它工具。

## 步骤

在Windows下需要使用MSYS/Cygwin的终端,在Linux下需要使用终端。

- 进入源代码目录，创建构建目录并进入。

```bash
mkdir build 
cd build
```

- 使用CMake生成工程文件。如为2M Flash需要打开BUILD_FLASH_2M。

```bash
#使用1M flash
cmake ../

#使用2M flash 
cmake -DBUILD_FLASH_2M=ON ../
```



- 根据上一步生成的工程文件使用对应工具（如make）执行编译

```bash
#windows或者MSYS2下执行make
make
#MINGW32/MINGW64下执行mingw32-make
mingw32-make
```

编译完成即可在构建目录得到镜像文件。

## 烧录

如需使用烧录，需要在使用CMake生成工程文件前设置WM_PORT变量,该变量用于指示烧录的串口(在Windows下为COMn，在linux下通常为ttyUSBn，n为数字，具体值需要在连接好硬件后通过设备管理器(Windows)或者dmesg(Linux)确定)。在终端下可使用以下命令设置WM_PORT环境变量：

```bash
export WM_PORT=实际串口
```

如设置成功,则编译完成后可执行以下烧录命令:

```bash
make flash
```

烧录过程中需要手动重启硬件两次，根据烧录程序的提示操作。

# 其他说明

WM_SDK_60X目录为官方公开的SDK，版本为WM_SDK_W60X_G3.04.00

