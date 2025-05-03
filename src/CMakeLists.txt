add_subdirectory(convert_file)
add_subdirectory(delay_parse)
add_subdirectory(sort_tape)
add_subdirectory(tape)

add_library(main OBJECT main.cpp)
add_library(generate_data OBJECT generate_data.cpp)
add_library(test_int_tape OBJECT test_int_tape.cpp)

target_include_directories(main PUBLIC tape_delays/include)


list(APPEND GCC_RELEASE_BUILD_TYPE_COMPILE_FLAGS
    -DNDEBUG
    -O2
)

list(APPEND GCC_DEBUG_BUILD_TYPE_COMPILE_FLAGS
    -g
    -Werror
    -Wall
    -Wextra
    -Wpedantic
    -Wcast-align
    -Wcast-qual
    -Wconversion
    -Wctor-dtor-privacy
    -Wenum-compare
    -Wfloat-equal
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
    -Wsign-conversion
    -Wsign-promo
)

if(CMAKE_BUILD_TYPE STREQUAL Release)
    message(STATUS "RELEASE BUILD TYPE")
    foreach(target IN ZIP_LISTS INT_TAPE_TARGETS)
        target_compile_options(
            ${target_0}
            PUBLIC
            ${GCC_RELEASE_BUILD_TYPE_COMPILE_FLAGS}
        )
    endforeach()
    foreach(target IN ZIP_LISTS GENERATOR_TARGETS)
        target_compile_options(
            ${target_0}
            PUBLIC
            ${GCC_RELEASE_BUILD_TYPE_COMPILE_FLAGS}
        )
    endforeach()
    foreach(target IN ZIP_LISTS TAPE_TESTS_TARGETS)
        target_compile_options(
            ${target_0}
            PUBLIC
            ${GCC_RELEASE_BUILD_TYPE_COMPILE_FLAGS}
        )
    endforeach()
endif()

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    message(STATUS "DEBUG BUILD TYPE")
    foreach(target IN ZIP_LISTS INT_TAPE_TARGETS)
        target_compile_options(
            ${target_0}
            PUBLIC
            ${GCC_DEBUG_BUILD_TYPE_COMPILE_FLAGS}
        )
    endforeach()
    foreach(target IN ZIP_LISTS GENERATOR_TARGETS)
        target_compile_options(
            ${target_0}
            PUBLIC
            ${GCC_DEBUG_BUILD_TYPE_COMPILE_FLAGS}
        )
    endforeach()
    foreach(target IN ZIP_LISTS TAPE_TESTS_TARGETS)
        target_compile_options(
            ${target_0}
            PUBLIC
            ${GCC_DEBUG_BUILD_TYPE_COMPILE_FLAGS}
        )
    endforeach()
endif()
