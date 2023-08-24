cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Release)

project(
    vector
    VERSION 0.1.0
    DESCRIPTION "Vector library for C"
    LANGUAGES C
)

add_executable(
    vector
    src/vector.c
)

target_link_libraries(vector
    Unity)

add_custom_target(
    run
    COMMAND vector
    DEPENDS vector
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
    VERBATIM
)

target_include_directories(
    vector
    PUBLIC
    src
)

add_library(Unity STATIC
    ../Unity/src/unity.c
)

target_include_directories(
    Unity
    PUBLIC
    ../Unity/src
)
