cmake_minimum_required(VERSION 3.22)
project(Study)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(Boost_USE_MULTITHREADED ON)

include(ExternalProject)

find_package(PkgConfig REQUIRED)
pkg_search_module(FUSE REQUIRED IMPORTED_TARGET fuse3)

add_executable(main main.cpp localfilesystem.h localfilesystem.cpp)

target_link_libraries(main PkgConfig::FUSE)
set_property(TARGET main PROPERTY CXX_STANDARD 17)

add_definitions(-D_FILE_OFFSET_BITS=64)
