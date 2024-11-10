cmake_minimum_required(VERSION 3.28)
project(WWIIISimulator)

set(CMAKE_CXX_STANDARD 17)

add_executable(WWIIISimulator src/main.cpp)

add_subdirectory(src)
add_subdirectory(libs)

target_link_libraries(WWIIISimulator PUBLIC src)