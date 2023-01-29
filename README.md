##### CMakeLists 分支

使用 CMakeLists.txt 对项目代码进行编译;



##### 1. cmake
- 在Android Studio2.2和以上版本，构建原生库的默认 工具 是CMake
- CMake是一个跨平台的构建工具，可以使用简洁的语句来描述所有平台的安装(编译过程)。能够输出各种各样的makefile或者project文件。CMake并不直接构建出最终的软件，而是产生其他工具脚本比如makefile，然后在依据这个工具的构建方式使用。
- CMake是一个比make更高级的编译配置工具，它可以根据不同的平台，不同的编译器，生成相应的makefile或者vcproj项目，从而达到跨平台的目的。Android Studio利用CMake生成的是ninja。ninja是一个小型的关注速度的构建系统。我们一般不需要关心ninja的脚本，只需要知道怎么配置CMake就行了
- CMake是一个跨平台的支持产出各种不同的构建建脚本的一个工具。

##### 2.cmake 源文件
CMake 源文件包含命令、注释、空格和换行
已 CMakeLists.txt 命名或者以 .cmake 为扩展名
可以通过 add_subdirectory() 命令把子目录的 CMake 源文件添加进来
CMake源文件中所有有效的语句都是命令，可以是内置命令或者自定义的函数或宏命令。



