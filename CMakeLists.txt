cmake_minimum_required (VERSION 3.11.0)
project (MyGame)
include_directories("src")

# use C++ standard version 17
set(CMAKE_CXX_STANDARD 17)
# produce non-optimized code with debug symbols
set(CMAKE_BUILD_TYPE Debug)

# Set the name of the executable to be produced
set(EXECUTABLE_NAME MyGame)

# Add all .c, - files under src/ directory
file(GLOB SOURCES_C "src/*.c")
# Add all .cpp, - files under src/ directory
file(GLOB SOURCES_CPP "src/*.cpp")
# Add all .hpp, - files under src/ directory
file(GLOB SOURCES_HPP "src/*.hpp")
# Add all .h, - files under src/ directory
file(GLOB SOURCES_H "src/*.h")
set(SOURCES ${SOURCES_C} ${SOURCES_CPP} ${SOURCES_H} ${SOURCES_HPP})

add_executable(${EXECUTABLE_NAME} ${SOURCES})
set(CMAKE_BUILD_TYPE Debug)

target_sources(MyGame PUBLIC ${SOURCES})
target_include_directories(MyGame PUBLIC .)
target_include_directories(MyGame PUBLIC src)

# Get a lot of warnings
if(MSVC)
    target_compile_options(MyGame PRIVATE /Wall)
else()
    # gcc and clang
    target_compile_options(MyGame PRIVATE -Wall -Wextra -pedantic -Wno-missing-field-initializers)
endif()

# Detect and add SFML and Box2D
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

# Find any version 2.X of SFML
# See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED network audio graphics window system)
include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})


find_package(Box2D REQUIRED)
include_directories(${Box2D_INCLUDE_DIR})
target_link_libraries(${EXECUTABLE_NAME} ${BOX2D_LIBRARY})

# For installing targets (not mandatory)
install (TARGETS ${EXECUTABLE_NAME} DESTINATION bin)