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
CMAKE_SOURCE_DIR = /source/build/tdlib-prefix/src/tdlib

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /source/build/tdlib-prefix/src/tdlib-build

# Include any dependencies generated for this target.
include benchmark/CMakeFiles/bench_http_server_fast.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include benchmark/CMakeFiles/bench_http_server_fast.dir/compiler_depend.make

# Include the progress variables for this target.
include benchmark/CMakeFiles/bench_http_server_fast.dir/progress.make

# Include the compile flags for this target's objects.
include benchmark/CMakeFiles/bench_http_server_fast.dir/flags.make

benchmark/CMakeFiles/bench_http_server_fast.dir/bench_http_server_fast.cpp.o: benchmark/CMakeFiles/bench_http_server_fast.dir/flags.make
benchmark/CMakeFiles/bench_http_server_fast.dir/bench_http_server_fast.cpp.o: /source/build/tdlib-prefix/src/tdlib/benchmark/bench_http_server_fast.cpp
benchmark/CMakeFiles/bench_http_server_fast.dir/bench_http_server_fast.cpp.o: benchmark/CMakeFiles/bench_http_server_fast.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/source/build/tdlib-prefix/src/tdlib-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object benchmark/CMakeFiles/bench_http_server_fast.dir/bench_http_server_fast.cpp.o"
	cd /source/build/tdlib-prefix/src/tdlib-build/benchmark && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT benchmark/CMakeFiles/bench_http_server_fast.dir/bench_http_server_fast.cpp.o -MF CMakeFiles/bench_http_server_fast.dir/bench_http_server_fast.cpp.o.d -o CMakeFiles/bench_http_server_fast.dir/bench_http_server_fast.cpp.o -c /source/build/tdlib-prefix/src/tdlib/benchmark/bench_http_server_fast.cpp

benchmark/CMakeFiles/bench_http_server_fast.dir/bench_http_server_fast.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/bench_http_server_fast.dir/bench_http_server_fast.cpp.i"
	cd /source/build/tdlib-prefix/src/tdlib-build/benchmark && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /source/build/tdlib-prefix/src/tdlib/benchmark/bench_http_server_fast.cpp > CMakeFiles/bench_http_server_fast.dir/bench_http_server_fast.cpp.i

benchmark/CMakeFiles/bench_http_server_fast.dir/bench_http_server_fast.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/bench_http_server_fast.dir/bench_http_server_fast.cpp.s"
	cd /source/build/tdlib-prefix/src/tdlib-build/benchmark && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /source/build/tdlib-prefix/src/tdlib/benchmark/bench_http_server_fast.cpp -o CMakeFiles/bench_http_server_fast.dir/bench_http_server_fast.cpp.s

# Object files for target bench_http_server_fast
bench_http_server_fast_OBJECTS = \
"CMakeFiles/bench_http_server_fast.dir/bench_http_server_fast.cpp.o"

# External object files for target bench_http_server_fast
bench_http_server_fast_EXTERNAL_OBJECTS =

benchmark/bench_http_server_fast: benchmark/CMakeFiles/bench_http_server_fast.dir/bench_http_server_fast.cpp.o
benchmark/bench_http_server_fast: benchmark/CMakeFiles/bench_http_server_fast.dir/build.make
benchmark/bench_http_server_fast: tdnet/libtdnet.a
benchmark/bench_http_server_fast: tdutils/libtdutils.a
benchmark/bench_http_server_fast: tdactor/libtdactor.a
benchmark/bench_http_server_fast: tdutils/libtdutils.a
benchmark/bench_http_server_fast: /usr/lib/x86_64-linux-gnu/libssl.so
benchmark/bench_http_server_fast: /usr/lib/x86_64-linux-gnu/libcrypto.so
benchmark/bench_http_server_fast: /usr/lib/x86_64-linux-gnu/libz.so
benchmark/bench_http_server_fast: benchmark/CMakeFiles/bench_http_server_fast.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/source/build/tdlib-prefix/src/tdlib-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bench_http_server_fast"
	cd /source/build/tdlib-prefix/src/tdlib-build/benchmark && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bench_http_server_fast.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
benchmark/CMakeFiles/bench_http_server_fast.dir/build: benchmark/bench_http_server_fast
.PHONY : benchmark/CMakeFiles/bench_http_server_fast.dir/build

benchmark/CMakeFiles/bench_http_server_fast.dir/clean:
	cd /source/build/tdlib-prefix/src/tdlib-build/benchmark && $(CMAKE_COMMAND) -P CMakeFiles/bench_http_server_fast.dir/cmake_clean.cmake
.PHONY : benchmark/CMakeFiles/bench_http_server_fast.dir/clean

benchmark/CMakeFiles/bench_http_server_fast.dir/depend:
	cd /source/build/tdlib-prefix/src/tdlib-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /source/build/tdlib-prefix/src/tdlib /source/build/tdlib-prefix/src/tdlib/benchmark /source/build/tdlib-prefix/src/tdlib-build /source/build/tdlib-prefix/src/tdlib-build/benchmark /source/build/tdlib-prefix/src/tdlib-build/benchmark/CMakeFiles/bench_http_server_fast.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : benchmark/CMakeFiles/bench_http_server_fast.dir/depend

