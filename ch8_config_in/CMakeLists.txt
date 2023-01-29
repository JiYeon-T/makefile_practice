cmake_minimum_required(VERSION 3.1)

project(Tutorial VERSION 1.2)

# 设置编译选项
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

# 默认打开或者关闭:将这个宏控默认打开
option(USE_MYMATH "Use tutorial provided math implementation:" OFF)

# 通过 config.h.in 生成 config.h 头文件
# ${PROJECT_BINARY_DIR} 目录下
configure_file(TutorialConfig.h.in TutorialConfig.h)

# 添加 mathfunctions 库, 使用添加子目录的方式
#add_subdirectory(MathFunctions)
# 不直接使用, 设置使用条件
if(USE_MYMATH)
    add_subdirectory(MathFunctions) # 添加子目录, 让子目录下的 CMakeLists.txt 参与编译
    list(APPEND EXTRA_LIBS MathFunctions) # 使用列表管理外部库
    list(APPEND EXTRA_INCLUDES ${PROJECT_SOURCE_DIR}/MathFunctions) # 使用列表管理外部库头文件的搜索路径
    message("US_MYMATH:${USE_MYMATH}")
    message("EXTRA_LIBS:${EXTRA_LIBS}")
    message("EXTRA_INCLUDES:${EXTRA_LIBS}")
endif()

# 添加源文件
add_executable(${PROJECT_NAME} main.cpp)

# 链接静态库和可执行文件
#target_link_libraries(${PROJECT_NAME} PUBLIC MathFunctions)
# 链接库的方式也进行修改
target_link_libraries(${PROJECT_NAME} PUBLIC ${EXTRA_LIBS})

# 将二进制树的路径添加到搜索路劲, 可以找到 TutorialConfig.h 文件(通过TutorialConfig.h.in 生成)
#target_include_directories(Tutorial PUBLIC
#                           ${PROJECT_BINARY_DIR},
#                           ${PROJECT_SOURCE_DIR}/MathFunctions
#)
# 头文件的搜索路径也要修改  
message("\n\nsearch dir:${PROJECT_BINARY_DIR} ${EXTRA_INCLUDES}")                        
target_include_directories(${PROJECT_NAME} PUBLIC
                           ${PROJECT_BINARY_DIR},
                           ${EXTRA_INCLUDES}
)  