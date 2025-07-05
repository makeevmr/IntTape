cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_COMPILER "/usr/bin/g++-13")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SOURCE_DIR "src/")

project(int_tape LANGUAGES CXX)

set(CMAKE_CXX_FLAGS_RELEASE "")
set(CMAKE_CXX_FLAGS_DEBUG "")

include_directories(${SOURCE_DIR})

list(APPEND INT_TAPE_TARGETS
    tape
    delay_parse
    convert_file
    sort_tape
    main
)

list(APPEND GENERATOR_TARGETS
    generate_data
)

list(APPEND TAPE_TESTS_TARGETS
    tape
    delay_parse
    convert_file
    sort_tape
    test_int_tape
)

add_subdirectory(src)

# int_tape
add_executable(int_tape)
target_link_libraries(int_tape PRIVATE ${INT_TAPE_TARGETS})

# generator
add_executable(generator)
target_link_libraries(generator PRIVATE ${GENERATOR_TARGETS})

# tape_tests
enable_testing()

find_package(GTest REQUIRED)

add_executable(tape_tests)
target_link_libraries(tape_tests PRIVATE
    GTest::GTest
    ${TAPE_TESTS_TARGETS}
)

add_test(tape_gtests tape_tests)
