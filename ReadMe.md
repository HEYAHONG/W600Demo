# 说明

这是一个使用[W600](https://www.winnermicro.com/html/1/156/158/497.html)开发的Demo（仅供测试）。

# 编译

## 工具

- gcc:用于编译wm_tool,windows平台不需要。
- arm-none-eabi-gcc :工具链，C运行库为newlib，windows平台下需使用MSYS2/Cygwin下的arm-none-eabi-gcc。
- cmake :生成工程文件。
- make ：执行编译，也可使用其它工具。

## 步骤

1. 创建目录
2. 使用CMake生成工程文件
3. 根据上一步生成的工程文件使用对应工具（如make）执行编译

编译完成即可得到bin文件。

# 其他说明

WM_SDK_60X目录为官方公开的SDK，版本为WM_SDK_W60X_G3.04.00

