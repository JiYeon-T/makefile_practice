# cmake parameters
# -G Specify a build system generator.
# Generators
# The following generators are available on this platform:
# Unix Makefiles               = Generates standard UNIX makefiles.
# Ninja                        = Generates build.ninja files.
# Watcom WMake                 = Generates Watcom WMake makefiles.
# CodeBlocks - Ninja           = Generates CodeBlocks project files.
# CodeBlocks - Unix Makefiles  = Generates CodeBlocks project files.
# CodeLite - Ninja             = Generates CodeLite project files.
# CodeLite - Unix Makefiles    = Generates CodeLite project files.
# Eclipse CDT4 - Ninja         = Generates Eclipse CDT 4.0 project files.
# Eclipse CDT4 - Unix Makefiles= Generates Eclipse CDT 4.0 project files.
# KDevelop3                    = Generates KDevelop 3 project files.
# KDevelop3 - Unix Makefiles   = Generates KDevelop 3 project files.
# Kate - Ninja                 = Generates Kate project files.
# Kate - Unix Makefiles        = Generates Kate project files.
# Sublime Text 2 - Ninja       = Generates Sublime Text 2 project files.
# -B 编译文件存放目录
# -S
mkdir build && cd build
# cmake -G "Unix Makefiles" -B ./build -S ./
cmake -G "Unix Makefiles" -B ./ -S ../
cd build && make -j32


# 编译方法:
# 1. mkdir build && cd build; cmake ..; make
# 2. ./build.sh

