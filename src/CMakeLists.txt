list(APPEND GCC_RELEASE_BUILD_TYPE_COMPILE_FLAGS -DNDEBUG -O2)

list(
  APPEND
  GCC_DEBUG_BUILD_TYPE_COMPILE_FLAGS
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
  -Wsign-promo)

if(CMAKE_BUILD_TYPE STREQUAL Release)
  message(STATUS "RELEASE BUILD TYPE")
  target_compile_options(${PROJECT_NAME}_tape_objs
                         PUBLIC ${GCC_RELEASE_BUILD_TYPE_COMPILE_FLAGS})
  target_compile_options(${PROJECT_NAME}_generate_objs
                         PUBLIC ${GCC_RELEASE_BUILD_TYPE_COMPILE_FLAGS})
endif()

if(CMAKE_BUILD_TYPE STREQUAL Debug)
  message(STATUS "DEBUG BUILD TYPE")
  target_compile_options(${PROJECT_NAME}_tape_objs
                         PUBLIC ${GCC_DEBUG_BUILD_TYPE_COMPILE_FLAGS})
  target_compile_options(${PROJECT_NAME}_generate_objs
                         PUBLIC ${GCC_DEBUG_BUILD_TYPE_COMPILE_FLAGS})
endif()

target_include_directories(${PROJECT_NAME}_tape_objs
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(${PROJECT_NAME}_generate_objs
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
