cmake_minimum_required(VERSION 3.22)
project(Study)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(Boost_USE_MULTITHREADED ON)

include(ExternalProject)

ExternalProject_Add(
    tgbot
    GIT_REPOSITORY https://github.com/reo7sp/tgbot-cpp.git
    GIT_TAG master 
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/tgbot
    STEP_TARGETS build
    BUILD_BYPRODUCTS ${CMAKE_BINARY_DIR}/tgbot/lib/libTgBot.a
)

find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost COMPONENTS system REQUIRED)
find_package(CURL)
include_directories(/usr/local/include ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR})
if (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    add_definitions(-DHAVE_CURL)
endif()

find_package(PkgConfig REQUIRED)
pkg_search_module(FUSE REQUIRED IMPORTED_TARGET fuse3)

add_executable(main main.cpp localfilesystem.h localfilesystem.cpp)

add_dependencies(main tgbot)

target_include_directories(main PRIVATE ${CMAKE_BINARY_DIR}/tgbot/include)
target_link_directories(main PRIVATE ${CMAKE_BINARY_DIR}/tgbot/lib)

target_link_libraries(main TgBot ${CMAKE_THREAD_LIBS_INIT} ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} ${CURL_LIBRARIES} PkgConfig::FUSE)
set_property(TARGET main PROPERTY CXX_STANDARD 17)

add_definitions(-D_FILE_OFFSET_BITS=64)
