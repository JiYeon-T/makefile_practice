cmake_minimum_required(VERSION 2.8)
# 静态库以及动态库的编译与移植
# 如果有需要 port 的接口, 如何联合编译....
project(static_lib_test)


# (1)基本编译: 
# gcc test.c -o test
# 运行: ./test

# 含有多个源文件时, 通过命令行编译
# gcc -o test test.c print_hello.c public.c 
# 这种方法对于拥有多个源文件的项目来说不现实, 所以需要使用 CMakeLists.txt 或者 makefile


# (2) 静态库的使用
# a.对于有源代码的项目, 不想让其他人看到这些代码, 自己将源文件封装成库 public, 最终生成 libpublic.a; 
# gcc -c 仅编译, 不链接;
# 例如: 这里封装 public.c
# gcc -c -o libpublic.a public.c

# 编译时的链接静态库的方法
# a.直接链接
# gcc -o test test.c print_hello.c libpublic.a

# b. -L 指定库文件搜索路径(链接库的目录), 否则会报错, 默认会去 /usr/lib 目录下查找;
#    -l 表示要链接哪个库
# /usr/bin/ld: cannot find -lpublic
# collect2: error: ld returned 1 exit status
# gcc -o test test.c -L/home/qz/code/makefile_practice/ch1_lib -lpublic
# gcc -o test test.c -L/home/qz/code/makefile_practice/ch1_lib -L/usr/lib -lpublic -lm

# 缺点:
# a. 如果修改了库文件, 必须要重新编译, 链接库文件才能生效;
# b. 每个程序使用单独的库文件, 占用内存较大;
# 优点:
# a. 编译速度快;

# (3) 动态库(共享库, 动态链接库)的使用
# 最终生成 libpublic.so

# 编译方法:
# -fPIC position indepdent code
gcc -fPIC -shared -o libpublic.so public.c

# 使用(链接)方法，与静态库相同
# 静态库(libpublic.a)和动态库(libpublic.so)同时存在的情况下, 编译器优先选择动态库;
# 找不到库文件 ./test: error while loading shared libraries: libpublic.so: cannot open shared object file: No such file or directory
# 使用了动态库的程序需要指定动态库文件的目录, Linux 使用 LD_LIBRARY_PATH 环境变量指定动态库文件的目录
# 设置环境变量:
# export LD_LIBRARY_PATH=/home/qz/code/makefile_practice/ch1_lib
# env | grep LD_LIBRARY_PATH
gcc -o test test.c print_hello.c -L/home/qz/code/makefile_practice/ch1_lib -lpublic



# (4) 与库文件有关的其他知识:
# 标准库的库文件所在目录: /usr/lib/gcc/x86_64-linux-gnu/
# 头文件目录: /usr/include/x86_64-linux-gnu/

# eg:oracle 编译示例， 提供的仅有头文件以及库文件
# -I:指定头文件目录; 
# -L:指定库文件目录
# -l:连接库文件
#g++ -g -Wall -Wno-write-strings -o createtable createtable.cpp -I/oracle/home/rdbms/public -L/oracle/home/lib -L. -lclntsh _ooci.cpp -lm -load_cache()
#g++ -g -Wall -Wno-write-strings -o inserttable inserttable.cpp -I/oracle/home/rdbms/public -L/oracle/home/lib -L. -lclntsh _ooci.cpp -lm -load_cache()
#g++ -g -Wall -Wno-write-strings -o selecttable selecttable.cpp -I/oracle/home/rdbms/public -L/oracle/home/lib -L. -lclntsh _ooci.cpp -lm -load_cache()

