cmake_minimum_required(VERSION 3.22)
project(Study)

set(CMAKE_CXX_STANDARD 17)

add_executable(Study main.cpp)

add_subdirectory(td)
target_link_libraries(Study PRIVATE Td::TdStatic)
