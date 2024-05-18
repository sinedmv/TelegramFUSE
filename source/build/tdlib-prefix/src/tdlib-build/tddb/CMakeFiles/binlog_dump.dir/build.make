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
include tddb/CMakeFiles/binlog_dump.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include tddb/CMakeFiles/binlog_dump.dir/compiler_depend.make

# Include the progress variables for this target.
include tddb/CMakeFiles/binlog_dump.dir/progress.make

# Include the compile flags for this target's objects.
include tddb/CMakeFiles/binlog_dump.dir/flags.make

tddb/CMakeFiles/binlog_dump.dir/td/db/binlog/binlog_dump.cpp.o: tddb/CMakeFiles/binlog_dump.dir/flags.make
tddb/CMakeFiles/binlog_dump.dir/td/db/binlog/binlog_dump.cpp.o: /source/build/tdlib-prefix/src/tdlib/tddb/td/db/binlog/binlog_dump.cpp
tddb/CMakeFiles/binlog_dump.dir/td/db/binlog/binlog_dump.cpp.o: tddb/CMakeFiles/binlog_dump.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/source/build/tdlib-prefix/src/tdlib-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tddb/CMakeFiles/binlog_dump.dir/td/db/binlog/binlog_dump.cpp.o"
	cd /source/build/tdlib-prefix/src/tdlib-build/tddb && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT tddb/CMakeFiles/binlog_dump.dir/td/db/binlog/binlog_dump.cpp.o -MF CMakeFiles/binlog_dump.dir/td/db/binlog/binlog_dump.cpp.o.d -o CMakeFiles/binlog_dump.dir/td/db/binlog/binlog_dump.cpp.o -c /source/build/tdlib-prefix/src/tdlib/tddb/td/db/binlog/binlog_dump.cpp

tddb/CMakeFiles/binlog_dump.dir/td/db/binlog/binlog_dump.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/binlog_dump.dir/td/db/binlog/binlog_dump.cpp.i"
	cd /source/build/tdlib-prefix/src/tdlib-build/tddb && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /source/build/tdlib-prefix/src/tdlib/tddb/td/db/binlog/binlog_dump.cpp > CMakeFiles/binlog_dump.dir/td/db/binlog/binlog_dump.cpp.i

tddb/CMakeFiles/binlog_dump.dir/td/db/binlog/binlog_dump.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/binlog_dump.dir/td/db/binlog/binlog_dump.cpp.s"
	cd /source/build/tdlib-prefix/src/tdlib-build/tddb && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /source/build/tdlib-prefix/src/tdlib/tddb/td/db/binlog/binlog_dump.cpp -o CMakeFiles/binlog_dump.dir/td/db/binlog/binlog_dump.cpp.s

# Object files for target binlog_dump
binlog_dump_OBJECTS = \
"CMakeFiles/binlog_dump.dir/td/db/binlog/binlog_dump.cpp.o"

# External object files for target binlog_dump
binlog_dump_EXTERNAL_OBJECTS =

tddb/binlog_dump: tddb/CMakeFiles/binlog_dump.dir/td/db/binlog/binlog_dump.cpp.o
tddb/binlog_dump: tddb/CMakeFiles/binlog_dump.dir/build.make
tddb/binlog_dump: tddb/libtddb.a
tddb/binlog_dump: tdactor/libtdactor.a
tddb/binlog_dump: tdutils/libtdutils.a
tddb/binlog_dump: sqlite/libtdsqlite.a
tddb/binlog_dump: /usr/lib/x86_64-linux-gnu/libcrypto.so
tddb/binlog_dump: /usr/lib/x86_64-linux-gnu/libz.so
tddb/binlog_dump: tddb/CMakeFiles/binlog_dump.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/source/build/tdlib-prefix/src/tdlib-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable binlog_dump"
	cd /source/build/tdlib-prefix/src/tdlib-build/tddb && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/binlog_dump.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tddb/CMakeFiles/binlog_dump.dir/build: tddb/binlog_dump
.PHONY : tddb/CMakeFiles/binlog_dump.dir/build

tddb/CMakeFiles/binlog_dump.dir/clean:
	cd /source/build/tdlib-prefix/src/tdlib-build/tddb && $(CMAKE_COMMAND) -P CMakeFiles/binlog_dump.dir/cmake_clean.cmake
.PHONY : tddb/CMakeFiles/binlog_dump.dir/clean

tddb/CMakeFiles/binlog_dump.dir/depend:
	cd /source/build/tdlib-prefix/src/tdlib-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /source/build/tdlib-prefix/src/tdlib /source/build/tdlib-prefix/src/tdlib/tddb /source/build/tdlib-prefix/src/tdlib-build /source/build/tdlib-prefix/src/tdlib-build/tddb /source/build/tdlib-prefix/src/tdlib-build/tddb/CMakeFiles/binlog_dump.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : tddb/CMakeFiles/binlog_dump.dir/depend

