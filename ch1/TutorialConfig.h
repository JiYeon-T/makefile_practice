// the configured options and settings for tutorial
// 会在  目录下生成一个 TutorialConfig.h 文件
// cmake 搜索时，2 和 3 将自动被设置好的版本号所替代
// project(tutorial VERSION 2.3)
// @Tutorial_VERSION_MAJOR@ 会被 CMakeLists.txt 中的变量 2 替代
// @Tutorial_VERSION_MINOR@
#define Tutorial_VERSION_MAJOR 2
#define Tutorial_VERSION_MINOR 3

//compile DATE
#define Tutorial_COMPILE_DATE 20220611
// 定义字符串类型宏定义的方法: "", VARIABLE 为 CMakeLists.txt 中定义的变量
#define Tutorila_COMPILE_AUTH "JiYeon_T"
