cmake_minimum_required(VERSION 3.22)
project(Study)

set(CMAKE_CXX_STANDARD 17)

include(ExternalProject)

ExternalProject_Add(
    tdlib
    GIT_REPOSITORY https://github.com/tdlib/td.git
    GIT_TAG v1.8.0  # Обновлено
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/tdlib
    STEP_TARGETS build
    BUILD_BYPRODUCTS ${CMAKE_BINARY_DIR}/tdlib/lib/libtdjson.a
)

add_executable(main main.cpp)

add_dependencies(main tdlib)

target_include_directories(main PRIVATE ${CMAKE_BINARY_DIR}/tdlib/include)
target_link_directories(main PRIVATE ${CMAKE_BINARY_DIR}/tdlib/lib)
target_link_libraries(main PRIVATE tdjson)
set_property(TARGET main PROPERTY CXX_STANDARD 17)
