cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 17)
project(three.math)

# option(THREE_MATH_BUILD_TEST FALSE)
option(THREE_MATH_MATH_PRECISION_DOUBLE FALSE)
option(THREE_MATH_DISABLE_SWIZZLE FALSE)

if ("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_CURRENT_SOURCE_DIR}")
    set(THREE_MATH_STANDALONE TRUE)
endif()

add_subdirectory(source)

if (THREE_MATH_STANDALONE)
    message(STATUS "configuring test")
    add_subdirectory(test)
endif()
