# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.31

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = D:\env\CMake\bin\cmake.exe

# The command to remove a file.
RM = D:\env\CMake\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\wtx_dev_workspace\tb14-_wtx_learn\vscode_workspace\cpp\wtx_test

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\wtx_dev_workspace\tb14-_wtx_learn\vscode_workspace\cpp\wtx_test\build

# Include any dependencies generated for this target.
include CMakeFiles/wtx_test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/wtx_test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/wtx_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/wtx_test.dir/flags.make

CMakeFiles/wtx_test.dir/codegen:
.PHONY : CMakeFiles/wtx_test.dir/codegen

CMakeFiles/wtx_test.dir/main.cpp.obj: CMakeFiles/wtx_test.dir/flags.make
CMakeFiles/wtx_test.dir/main.cpp.obj: CMakeFiles/wtx_test.dir/includes_CXX.rsp
CMakeFiles/wtx_test.dir/main.cpp.obj: D:/wtx_dev_workspace/tb14-_wtx_learn/vscode_workspace/cpp/wtx_test/main.cpp
CMakeFiles/wtx_test.dir/main.cpp.obj: CMakeFiles/wtx_test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\wtx_dev_workspace\tb14-_wtx_learn\vscode_workspace\cpp\wtx_test\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/wtx_test.dir/main.cpp.obj"
	D:\env\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/wtx_test.dir/main.cpp.obj -MF CMakeFiles\wtx_test.dir\main.cpp.obj.d -o CMakeFiles\wtx_test.dir\main.cpp.obj -c D:\wtx_dev_workspace\tb14-_wtx_learn\vscode_workspace\cpp\wtx_test\main.cpp

CMakeFiles/wtx_test.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/wtx_test.dir/main.cpp.i"
	D:\env\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\wtx_dev_workspace\tb14-_wtx_learn\vscode_workspace\cpp\wtx_test\main.cpp > CMakeFiles\wtx_test.dir\main.cpp.i

CMakeFiles/wtx_test.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/wtx_test.dir/main.cpp.s"
	D:\env\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\wtx_dev_workspace\tb14-_wtx_learn\vscode_workspace\cpp\wtx_test\main.cpp -o CMakeFiles\wtx_test.dir\main.cpp.s

# Object files for target wtx_test
wtx_test_OBJECTS = \
"CMakeFiles/wtx_test.dir/main.cpp.obj"

# External object files for target wtx_test
wtx_test_EXTERNAL_OBJECTS =

bin/wtx_test.exe: CMakeFiles/wtx_test.dir/main.cpp.obj
bin/wtx_test.exe: CMakeFiles/wtx_test.dir/build.make
bin/wtx_test.exe: D:/wtx_dev_workspace/boost_install/lib/libboost_filesystem-mgw12-mt-x64-1_88.a
bin/wtx_test.exe: D:/wtx_dev_workspace/boost_install/lib/libboost_system-mgw12-mt-x64-1_88.a
bin/wtx_test.exe: D:/wtx_dev_workspace/boost_install/lib/libboost_atomic-mgw12-mt-x64-1_88.a
bin/wtx_test.exe: CMakeFiles/wtx_test.dir/linkLibs.rsp
bin/wtx_test.exe: CMakeFiles/wtx_test.dir/objects1.rsp
bin/wtx_test.exe: CMakeFiles/wtx_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\wtx_dev_workspace\tb14-_wtx_learn\vscode_workspace\cpp\wtx_test\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin\wtx_test.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\wtx_test.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/wtx_test.dir/build: bin/wtx_test.exe
.PHONY : CMakeFiles/wtx_test.dir/build

CMakeFiles/wtx_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\wtx_test.dir\cmake_clean.cmake
.PHONY : CMakeFiles/wtx_test.dir/clean

CMakeFiles/wtx_test.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\wtx_dev_workspace\tb14-_wtx_learn\vscode_workspace\cpp\wtx_test D:\wtx_dev_workspace\tb14-_wtx_learn\vscode_workspace\cpp\wtx_test D:\wtx_dev_workspace\tb14-_wtx_learn\vscode_workspace\cpp\wtx_test\build D:\wtx_dev_workspace\tb14-_wtx_learn\vscode_workspace\cpp\wtx_test\build D:\wtx_dev_workspace\tb14-_wtx_learn\vscode_workspace\cpp\wtx_test\build\CMakeFiles\wtx_test.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/wtx_test.dir/depend

