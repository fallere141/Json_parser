cmake_minimum_required(VERSION 3.24)
project(json_decode)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(compile-time-regular-expressions)
include_directories(compile-time-regular-expressions/include)


add_executable(json_decode main.cpp json4.cpp json5.cpp)
target_link_libraries(json_decode ctre)

add_executable(json_decode2 main2.cpp json4.cpp json5.cpp)
target_link_libraries(json_decode2 ctre)
#add_executable(json.cpp json.cpp)
#add_executable(Json2.cpp Json2.cpp)
