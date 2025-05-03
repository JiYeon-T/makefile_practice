cmake_minimum_required(VERSION 3.23.0)
project(condition_cmake VERSION 1.5)
# 条件构建 OPTION


message("")
message(STATUS "CMakeExpMaster")

# TODO: option 为什么不生效????
# TEST_OPTION 默认为 ABC
# 同时会定义宏：TEST_OPTION
option(TEST_OPTION "test option" ON)

# 是否定义了 TEST_OPTION
# "DEFINED" 的使用
if(DEFINED TEST_OPTION)
	message(STATUS "TEST_OPTION:" ${TEST_OPTION})
	# 添加宏定义
	add_definitions(-DTEST_OPTION)
# 添加定义
else()
	message(STATUS "TEST_OPTION:${TEST_OPTION}")
endif()

# "NOT" 的使用:
if(NOT TEST_OPTION)
	message(STATUS "NOT TEST_OPTION ON")
else()
	message(STATUS "NOT-TEST_OPTION OFF")
endif()


# 添加子工程
add_subdirectory(sub)

# 生成可执行文件
add_executable(${PROJECT_NAME}_bin test.c)

# 添加头文件路径
target_include_directories(${PROJECT_NAME}_bin 
	PUBLIC
	${PROJECT_SOURCE_DIR}/include
)