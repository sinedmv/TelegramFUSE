# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /source

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /source/build

# Include any dependencies generated for this target.
include CMakeFiles/Study.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Study.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Study.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Study.dir/flags.make

CMakeFiles/Study.dir/main.cpp.o: CMakeFiles/Study.dir/flags.make
CMakeFiles/Study.dir/main.cpp.o: /source/main.cpp
CMakeFiles/Study.dir/main.cpp.o: CMakeFiles/Study.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/source/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Study.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Study.dir/main.cpp.o -MF CMakeFiles/Study.dir/main.cpp.o.d -o CMakeFiles/Study.dir/main.cpp.o -c /source/main.cpp

CMakeFiles/Study.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Study.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /source/main.cpp > CMakeFiles/Study.dir/main.cpp.i

CMakeFiles/Study.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Study.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /source/main.cpp -o CMakeFiles/Study.dir/main.cpp.s

# Object files for target Study
Study_OBJECTS = \
"CMakeFiles/Study.dir/main.cpp.o"

# External object files for target Study
Study_EXTERNAL_OBJECTS =

Study: CMakeFiles/Study.dir/main.cpp.o
Study: CMakeFiles/Study.dir/build.make
Study: CMakeFiles/Study.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/source/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Study"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Study.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Study.dir/build: Study
.PHONY : CMakeFiles/Study.dir/build

CMakeFiles/Study.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Study.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Study.dir/clean

CMakeFiles/Study.dir/depend:
	cd /source/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /source /source /source/build /source/build /source/build/CMakeFiles/Study.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/Study.dir/depend

