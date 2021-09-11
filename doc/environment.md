# Ubuntu 20.04

使用以下命令安装对应软件包即可。需要连接互联网或者配置本地镜像源。

```bash
sudo apt install build-essential gcc gcc-arm-none-eabi make cmake python3 python3-pip
sudo python3 -m pip install kconfiglib
```

# Windows

windows应当安装[msys2](https://www.msys2.org/)。下载速度慢可使用镜像下载:

- https://mirrors.tuna.tsinghua.edu.cn/msys2/distrib/
- https://mirrors.ustc.edu.cn/msys2/distrib/

安装完成后，会出现以下入口(包括但不限于):

- msys2  (MSYS2 MSYS)
- mingw32 (MSYS2 MinGW 32-bit)
- mingw64 (MSYS2 MinGW 64-bit)

通常情况下，只需要使用mingw32/mingw64。为防止以前安装的软件包干扰，建议使用新安装的msys2(可在安装时修改安装路径保留原有安装)。

## Mingw32

使用以下命令安装对应软件包即可。需要连接互联网或者配置本地镜像源。

``` bash
pacman -S mingw-w64-i686-arm-none-eabi-gcc mingw-w64-i686-cmake mingw-w64-i686-make make  mingw-w64-i686-ninja
```

由于未安装Python,不可使用Kconfig。生成工程时应改为使用以下命令（-G 指定生成工程的类型， "MinGW Makefiles"为使用mingw32-make的工程，默认情况下可能生成ninja的工程，需要使用ninja替代make/mingw32-make）:

```bash
 cmake -G "MinGW Makefiles" -DUSE_KCONFIG=OFF 源代码所在目录
```



## Mingw64

使用以下命令安装对应软件包即可。需要连接互联网或者配置本地镜像源。

```bash
pacman -S mingw-w64-x86_64-arm-none-eabi-gcc mingw-w64-x86_64-cmake mingw-w64-x86_64-make make  mingw-w64-x86_64-ninja
```
由于未安装Python,不可使用Kconfig，需要添加-DUSE_KCONFIG=OFF。生成工程时应改为使用以下命令（-G 指定生成工程的类型， "MinGW Makefiles"为使用mingw32-make的工程，默认情况下可能生成ninja的工程，需要使用ninja替代make/mingw32-make）:

```bash
 cmake -G "MinGW Makefiles" -DUSE_KCONFIG=OFF 源代码所在目录
```



## Python

由于msys2最新自带的python版本太高(20210911)，因此不可直接使用msys2自带的安装包。

受到[windows-curses](https://pypi.org/project/windows-curses)支持版本的限制,推荐安装python 3.8以下的[python](https://www.python.org/)并添加至系统PATH目录。

### 使用

1.需要将python在windows下的目录转换为在msys下的目录,转换方法如下：

- 所有盘符直接转化为/x（x为盘符），如C:转化为/C
- 所有的\替换为/

如python.exe所在目录为C:\Python\，在msys2下的目录为/C/Python/。

2.打开msys2 mingw32/mingw64终端,将python目录添加至PATH目录。

```bash
export PATH=Python目录:$PATH
```

3.生成工程时不添加-DUSE_KCONFIG=OFF,例如（-G 指定生成工程的类型， "MinGW Makefiles"为使用mingw32-make的工程，默认情况下可能生成ninja的工程，需要使用ninja替代make/mingw32-make）:

```bash
cmake -G "MinGW Makefiles"  源代码所在目录
```



