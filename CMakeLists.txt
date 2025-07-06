cmake_minimum_required(VERSION 3.31)
project(matrices)

set(CMAKE_CXX_STANDARD 23)

if(ENABLE_TESTING)
enable_testing()
add_subdirectory(googletest)
add_subdirectory(tests)
endif()

add_library(matrices INTERFACE)
target_include_directories(matrices INTERFACE public_include)
