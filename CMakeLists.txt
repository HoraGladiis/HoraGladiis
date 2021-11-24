cmake_minimum_required(VERSION 3.10)

project(HoraGladiis VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)

# Windows specific config
IF (WIN32)
    # Include local sfml cmake config
    set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1/lib/cmake/SFML")
    # Link sfml statically
    set(SFML_STATIC_LIBRARIES TRUE)
ENDIF()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Find SFML shared libraries
find_package(SFML 2.5.1 COMPONENTS graphics window system REQUIRED)

FILE(
  GLOB
  SOURCES
  "Tile.cpp"
  "Tile.hpp"
  "Tileset.cpp"
  "Tileset.hpp"
  "Tilemap.cpp"
  "Tilemap.hpp"
  "Character.cpp"
  "Character.hpp"
  "Camera.cpp"
  "Camera.hpp"
  "EventHandler.cpp"
  "EventHandler.hpp"
  "DeltaTime.cpp"
  "DeltaTime.hpp"
  "GameLevel.cpp"
  "GameLevel.hpp"
  "Player.cpp"
  "Player.hpp"
  "Game.cpp"
  "Game.hpp"
  "misc.hpp"
  "main.cpp"
)

FILE(
  COPY "${CMAKE_CURRENT_SOURCE_DIR}/assets"
  DESTINATION "${CMAKE_CURRENT_BINARY_DIR}"
)

add_executable(HoraGladiis ${SOURCES})
target_link_libraries(HoraGladiis sfml-graphics sfml-window sfml-system)
