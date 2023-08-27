cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_C_COMPILER clang)

add_subdirectory(external)

project(
    vector
    VERSION 0.1.0
    DESCRIPTION "Vector library for C"
    LANGUAGES C
)

add_executable(
    test_vector
    test/test_main.c
    src/vector.c
)
target_include_directories(
    test_vector
    PUBLIC
    src
)

target_link_libraries(test_vector
    unity)

add_custom_target(
    run_test
    COMMAND test_vector
    DEPENDS test_vector
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
    VERBATIM
)
