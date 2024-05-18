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
include benchmark/CMakeFiles/bench_http_reader.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include benchmark/CMakeFiles/bench_http_reader.dir/compiler_depend.make

# Include the progress variables for this target.
include benchmark/CMakeFiles/bench_http_reader.dir/progress.make

# Include the compile flags for this target's objects.
include benchmark/CMakeFiles/bench_http_reader.dir/flags.make

benchmark/CMakeFiles/bench_http_reader.dir/bench_http_reader.cpp.o: benchmark/CMakeFiles/bench_http_reader.dir/flags.make
benchmark/CMakeFiles/bench_http_reader.dir/bench_http_reader.cpp.o: /source/build/tdlib-prefix/src/tdlib/benchmark/bench_http_reader.cpp
benchmark/CMakeFiles/bench_http_reader.dir/bench_http_reader.cpp.o: benchmark/CMakeFiles/bench_http_reader.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/source/build/tdlib-prefix/src/tdlib-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object benchmark/CMakeFiles/bench_http_reader.dir/bench_http_reader.cpp.o"
	cd /source/build/tdlib-prefix/src/tdlib-build/benchmark && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT benchmark/CMakeFiles/bench_http_reader.dir/bench_http_reader.cpp.o -MF CMakeFiles/bench_http_reader.dir/bench_http_reader.cpp.o.d -o CMakeFiles/bench_http_reader.dir/bench_http_reader.cpp.o -c /source/build/tdlib-prefix/src/tdlib/benchmark/bench_http_reader.cpp

benchmark/CMakeFiles/bench_http_reader.dir/bench_http_reader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/bench_http_reader.dir/bench_http_reader.cpp.i"
	cd /source/build/tdlib-prefix/src/tdlib-build/benchmark && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /source/build/tdlib-prefix/src/tdlib/benchmark/bench_http_reader.cpp > CMakeFiles/bench_http_reader.dir/bench_http_reader.cpp.i

benchmark/CMakeFiles/bench_http_reader.dir/bench_http_reader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/bench_http_reader.dir/bench_http_reader.cpp.s"
	cd /source/build/tdlib-prefix/src/tdlib-build/benchmark && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /source/build/tdlib-prefix/src/tdlib/benchmark/bench_http_reader.cpp -o CMakeFiles/bench_http_reader.dir/bench_http_reader.cpp.s

# Object files for target bench_http_reader
bench_http_reader_OBJECTS = \
"CMakeFiles/bench_http_reader.dir/bench_http_reader.cpp.o"

# External object files for target bench_http_reader
bench_http_reader_EXTERNAL_OBJECTS =

benchmark/bench_http_reader: benchmark/CMakeFiles/bench_http_reader.dir/bench_http_reader.cpp.o
benchmark/bench_http_reader: benchmark/CMakeFiles/bench_http_reader.dir/build.make
benchmark/bench_http_reader: tdnet/libtdnet.a
benchmark/bench_http_reader: tdutils/libtdutils.a
benchmark/bench_http_reader: tdactor/libtdactor.a
benchmark/bench_http_reader: tdutils/libtdutils.a
benchmark/bench_http_reader: /usr/lib/x86_64-linux-gnu/libssl.so
benchmark/bench_http_reader: /usr/lib/x86_64-linux-gnu/libcrypto.so
benchmark/bench_http_reader: /usr/lib/x86_64-linux-gnu/libz.so
benchmark/bench_http_reader: benchmark/CMakeFiles/bench_http_reader.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/source/build/tdlib-prefix/src/tdlib-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bench_http_reader"
	cd /source/build/tdlib-prefix/src/tdlib-build/benchmark && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bench_http_reader.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
benchmark/CMakeFiles/bench_http_reader.dir/build: benchmark/bench_http_reader
.PHONY : benchmark/CMakeFiles/bench_http_reader.dir/build

benchmark/CMakeFiles/bench_http_reader.dir/clean:
	cd /source/build/tdlib-prefix/src/tdlib-build/benchmark && $(CMAKE_COMMAND) -P CMakeFiles/bench_http_reader.dir/cmake_clean.cmake
.PHONY : benchmark/CMakeFiles/bench_http_reader.dir/clean

benchmark/CMakeFiles/bench_http_reader.dir/depend:
	cd /source/build/tdlib-prefix/src/tdlib-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /source/build/tdlib-prefix/src/tdlib /source/build/tdlib-prefix/src/tdlib/benchmark /source/build/tdlib-prefix/src/tdlib-build /source/build/tdlib-prefix/src/tdlib-build/benchmark /source/build/tdlib-prefix/src/tdlib-build/benchmark/CMakeFiles/bench_http_reader.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : benchmark/CMakeFiles/bench_http_reader.dir/depend

