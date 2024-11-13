include(FetchContent)

FetchContent_Declare(
  SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 2.6.x
  GIT_SHALLOW ON
  EXCLUDE_FROM_ALL
  SYSTEM
)

FetchContent_Declare(
  box2d
  GIT_REPOSITORY https://github.com/erincatto/box2d.git
  GIT_TAG v3.0.0
  GIT_SHALLOW ON
  EXCLUDE_FROM_ALL
  SYSTEM
)

FetchContent_Declare(
  box2cpp
  GIT_REPOSITORY https://github.com/HolyBlackCat/box2cpp.git
  GIT_TAG box2d-3.0.0
  GIT_SHALLOW ON
  EXCLUDE_FROM_ALL
  SYSTEM
)

FetchContent_MakeAvailable(SFML box2d box2cpp)

add_library(libs INTERFACE)

target_link_libraries(libs INTERFACE
  sfml-audio
  sfml-graphics
  sfml-network
  box2d
)

target_include_directories(libs INTERFACE
  ${box2cpp_SOURCE_DIR}/include
)