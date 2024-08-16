cmake_minimum_required(VERSION 3.24)
project(json_decode)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(compile-time-regular-expressions)
include_directories(compile-time-regular-expressions/include)

add_executable(example example.cpp)
target_link_libraries(example ctre)