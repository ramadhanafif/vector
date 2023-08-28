cmake_minimum_required(VERSION 3.10)

project(
    vector
    VERSION 0.1.0
    DESCRIPTION "Vector library for C"
    LANGUAGES C
)

add_library(
    vector
    src/vector.c
)
target_include_directories(
    vector
    PUBLIC
    src
)

if(PROJECT_IS_TOP_LEVEL)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    set(CMAKE_BUILD_TYPE Debug)

    message("PROJECT IS TOP LEVEL, building tests")
    message("run test with `make -C ${CMAKE_BINARY_DIR} runtest`")
    add_subdirectory(external)
    add_executable(
        test_vector
        test/test_main.c
    )

    target_include_directories(
        test_vector
        PUBLIC
        src
    )

    target_link_libraries(test_vector
        unity vector)

    add_custom_target(
        runtest
        COMMAND test_vector
        DEPENDS test_vector
        WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
        VERBATIM
    )
endif()
