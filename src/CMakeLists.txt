file(GLOB SOURCES_CPP "*.cpp")

add_library(src ${SOURCES_CPP})

target_include_directories(src PUBLIC include)

target_link_libraries(src PUBLIC libs)