
# 通过源文件生成 libMathFunctions.a 静态库
# 外部库想要使用就要链接这个库文件
add_library(MathFunctions STATIC mysqrt.cpp)