cmake_minimum_required(VERSION 3.22)
project(Study)

set(CMAKE_CXX_STANDARD 17)

include(ExternalProject)

ExternalProject_Add(
    tgbot
    GIT_REPOSITORY https://github.com/reo7sp/tgbot-cpp.git
    GIT_TAG master  # Укажите необходимую ветку или тег
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/tgbot
    STEP_TARGETS build
    BUILD_BYPRODUCTS ${CMAKE_BINARY_DIR}/tgbot/lib/libTgBot.a
)

add_executable(main main.cpp)

add_dependencies(main tgbot)

target_include_directories(main PRIVATE ${CMAKE_BINARY_DIR}/tgbot/include)
target_link_directories(main PRIVATE ${CMAKE_BINARY_DIR}/tgbot/lib)

target_link_libraries(main PRIVATE TgBot)
set_property(TARGET main PROPERTY CXX_STANDARD 17)
