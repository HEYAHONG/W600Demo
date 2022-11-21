# **使用rt-thread开发的Demo请见[W600RtthreadDemo](https://github.com/HEYAHONG/W600RtthreadDemo.git)**

# 说明

这是一个使用[W600](https://www.winnermicro.com/html/1/156/158/497.html)开发的Demo（仅供测试）。
## 源代码下载

由于本源代码包含第三方源代码,故直接下载可能有部分源代码缺失，需要通过以下方法解决:

- 在进行git clone 使用--recurse-submodules参数。

- 若已通过git clone下载,则在源代码目录中执行以下命令下载子模块:

  ```bash
   git submodule update --init --recursive
  ```

## 资源文件

类似于桌面程序的资源文件。源代码实现的目录为 [rc](rc/)。

在固件编写中，很多时候需要大量的固定数据，直接手工嵌入到C文件里比较麻烦。

通过读取文件转换到对应C文件可大大节省时间，可添加常用的文件（如各种证书）或者不适宜放在可读写的文件系统中的文件(如需要在格式化中保留或者初始参数)。转换程序源代码为[rc/fsgen.cpp](rc/fsgen.cpp)。

使用步骤如下:

- 将待添加的文件放入 rc/fs目录下。

- 使用文件名调用以下函数(需包含相应头文件RC.h):

  ```c++
  //通过名称获取资源大小
  size_t RCGetSize(const char * name);
  
  //通过名称获取资源指针
  const unsigned char * RCGetHandle(const char * name);
  ```



# 编译

## 工具

- gcc:用于编译wm_tool,windows平台不需要。
- arm-none-eabi-gcc :工具链，C运行库为newlib，windows平台下需使用MSYS2 Mingw32/Mingw64下的arm-none-eabi-gcc。
- cmake :生成工程文件。
- make :执行编译，也可使用其它工具(如ninja)。
- python:执行脚本，可能需要手动安装pip。

某些系统的运行环境配置见  [doc/environment.md](doc/environment.md)

除了自行安装上述工具，在Linux下还可直接使用docker(需要自行安装docker)命令直接进入编译环境：

```bash
sudo docker run -it --rm -u  `id -u`:`id -g` -v `pwd`:/work -w /work heyahong/buildenv-ubuntu22.04:w600
#更多关于此docker镜像的说明见https://hub.docker.com/r/heyahong/buildenv-ubuntu22.04
```

## 步骤

在Windows下需要使用MSYS的Mingw32/mingw64终端,在Linux下需要使用终端。

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



- 根据上一步生成的工程文件使用对应工具（如make）执行编译。

```bash
#Linux下执行make
make
#MINGW32/MINGW64下执行mingw32-make
mingw32-make
```

编译完成即可在构建目录得到镜像文件。

- 在生成工程文件未禁止使用Kconfig(-DUSE_KCONFIG=OFF)时，可使用menuconfig目标进行Kconfig配置。

```bash
#Linux下执行make
make menuconfig
#MINGW32/MINGW64下执行mingw32-make
mingw32-make menuconfig
```



## 烧录

如需使用烧录，需要在使用CMake生成工程文件前设置WM_PORT变量,该变量用于指示烧录的串口(在Windows下为COMn，在linux下通常为ttyUSBn，n为数字，具体值需要在连接好硬件后通过设备管理器(Windows)或者dmesg(Linux)确定)。在终端下可使用以下命令设置WM_PORT环境变量：

```bash
export WM_PORT=实际串口
```

如设置成功,则编译完成后可执行以下烧录命令(Linux下可能要使用sudo):

```bash
#Linux下执行make
make flash
#MINGW32/MINGW64下执行mingw32-make
mingw32-make flash
```

烧录过程中需要手动重启硬件两次，根据烧录程序的提示操作。

# 其他说明

WM_SDK_60X目录为官方公开的SDK，版本为WM_SDK_W60X_G3.04.00



# 其它开发方式说明

## RT-Thread

除了使用SDK进行开发,还可使用RT-Thread进行开发。

支持的BSP目录为：bsp/w60x

### 相关链接

- https://github.com/RT-Thread/rt-thread.git
- https://gitee.com/rtthread/rt-thread.git

## LuatOS

除了进行C/C++开发，还可进行lua开发。

支持的BSP目录为:bsp/air640w

### 相关链接

- https://github.com/openLuat/LuatOS.git
- https://gitee.com/openLuat/LuatOS.git
