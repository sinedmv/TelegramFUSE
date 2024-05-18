cmake_minimum_required(VERSION 3.27)
project(Study)

set(CMAKE_CXX_STANDARD 17)

set(Td_DIR "/")
find_package(Td REQUIRED)

add_executable(YourExecutableName main.cpp)
target_link_libraries(YourExecutableName Td::TdClient Td::TdJson Td::TdApi Td::TdCore)
