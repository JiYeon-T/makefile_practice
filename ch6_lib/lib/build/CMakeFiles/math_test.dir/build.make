# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = C:/Users/qz/cmake-3.23.0-rc3-windows-x86_64/bin/cmake.exe

# The command to remove a file.
RM = C:/Users/qz/cmake-3.23.0-rc3-windows-x86_64/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:/Files/GitFile/C_notebook/CMakeList_Test/ch6_lib/lib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:/Files/GitFile/C_notebook/CMakeList_Test/ch6_lib/lib/build

# Include any dependencies generated for this target.
include CMakeFiles/math_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/math_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/math_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/math_test.dir/flags.make

CMakeFiles/math_test.dir/src/math_test.c.obj: CMakeFiles/math_test.dir/flags.make
CMakeFiles/math_test.dir/src/math_test.c.obj: ../src/math_test.c
CMakeFiles/math_test.dir/src/math_test.c.obj: CMakeFiles/math_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:/Files/GitFile/C_notebook/CMakeList_Test/ch6_lib/lib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/math_test.dir/src/math_test.c.obj"
	C:/MinGW/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/math_test.dir/src/math_test.c.obj -MF CMakeFiles/math_test.dir/src/math_test.c.obj.d -o CMakeFiles/math_test.dir/src/math_test.c.obj -c D:/Files/GitFile/C_notebook/CMakeList_Test/ch6_lib/lib/src/math_test.c

CMakeFiles/math_test.dir/src/math_test.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/math_test.dir/src/math_test.c.i"
	C:/MinGW/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:/Files/GitFile/C_notebook/CMakeList_Test/ch6_lib/lib/src/math_test.c > CMakeFiles/math_test.dir/src/math_test.c.i

CMakeFiles/math_test.dir/src/math_test.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/math_test.dir/src/math_test.c.s"
	C:/MinGW/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:/Files/GitFile/C_notebook/CMakeList_Test/ch6_lib/lib/src/math_test.c -o CMakeFiles/math_test.dir/src/math_test.c.s

# Object files for target math_test
math_test_OBJECTS = \
"CMakeFiles/math_test.dir/src/math_test.c.obj"

# External object files for target math_test
math_test_EXTERNAL_OBJECTS =

libmath_test.a: CMakeFiles/math_test.dir/src/math_test.c.obj
libmath_test.a: CMakeFiles/math_test.dir/build.make
libmath_test.a: CMakeFiles/math_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:/Files/GitFile/C_notebook/CMakeList_Test/ch6_lib/lib/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libmath_test.a"
	$(CMAKE_COMMAND) -P CMakeFiles/math_test.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/math_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/math_test.dir/build: libmath_test.a
.PHONY : CMakeFiles/math_test.dir/build

CMakeFiles/math_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/math_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/math_test.dir/clean

CMakeFiles/math_test.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" D:/Files/GitFile/C_notebook/CMakeList_Test/ch6_lib/lib D:/Files/GitFile/C_notebook/CMakeList_Test/ch6_lib/lib D:/Files/GitFile/C_notebook/CMakeList_Test/ch6_lib/lib/build D:/Files/GitFile/C_notebook/CMakeList_Test/ch6_lib/lib/build D:/Files/GitFile/C_notebook/CMakeList_Test/ch6_lib/lib/build/CMakeFiles/math_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/math_test.dir/depend
