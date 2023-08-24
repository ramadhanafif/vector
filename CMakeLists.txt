cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Release)

project(
    vector
    VERSION 0.1.0
    DESCRIPTION "Vector library for C"
    LANGUAGES C
)

add_executable(
    test
    src/test_main.c
    src/vector.c
)
target_include_directories(
    test
    PUBLIC
    src
)

# target_link_libraries(vector
#     Unity)

add_custom_target(
    run
    COMMAND test
    DEPENDS test
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
    VERBATIM
)


# add_library(Unity STATIC
#     ../Unity/src/unity.c
# )
#
# target_include_directories(
#     Unity
#     PUBLIC
#     ../Unity/src
# )
