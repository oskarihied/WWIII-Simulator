cmake_minimum_required(VERSION 3.22)
project(WWIIISimulator)

set(CMAKE_CXX_STANDARD 20)

add_executable(WWIIISimulator src/main.cpp)
add_executable(Tests EXCLUDE_FROM_ALL tests/main.cpp)

add_subdirectory(src)
add_subdirectory(libs)

target_link_libraries(WWIIISimulator PUBLIC src)
target_link_libraries(Tests PUBLIC src)