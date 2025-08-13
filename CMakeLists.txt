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

add_library(
  ${PROJECT_NAME}_tape_objs OBJECT
  src/convert_file/convert_file.cpp
  src/convert_file/convert_file.hpp
  src/delay_parse/delay_parse.cpp
  src/delay_parse/delay_parse.hpp
  src/sort_tape/sort_tape.cpp
  src/sort_tape/sort_tape.hpp
  src/tape/tape.cpp
  src/tape/tape.hpp
  src/tape_delays/tape_delays.hpp)

add_library(${PROJECT_NAME}_generate_objs OBJECT src/generate_data.cpp)

add_subdirectory(${SOURCE_DIR})

# int_tape
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_tape_objs)

# generator
add_executable(generator)
target_link_libraries(generator PRIVATE ${PROJECT_NAME}_generate_objs)

# tape_tests
enable_testing()

find_package(GTest REQUIRED)

add_executable(tape_tests src/test_int_tape.cpp)
target_link_libraries(tape_tests PRIVATE GTest::GTest ${PROJECT_NAME}_tape_objs)

add_test(tape_gtests tape_tests)
