cmake_minimum_required(VERSION 3.10)

project(HoraGladiis_tests VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include(CTest)

set(TGUI_BACKEND "SFML_GRAPHICS")
set(TGUI_SHARED_LIBS "FALSE")

find_package(doctest REQUIRED)
find_package(SFML 2.5.1 COMPONENTS graphics window system REQUIRED)
find_package(TGUI 0.10 REQUIRED)

FILE(
  COPY "${CMAKE_CURRENT_SOURCE_DIR}/samples"
  DESTINATION "${CMAKE_CURRENT_BINARY_DIR}"
)

add_executable(test1 test1.cpp doctest.h)
add_executable(test2 test2.cpp doctest.h)
add_executable(test3 ../src/Tile.cpp ../src/Tile.hpp collision_test.cpp doctest.h)
add_executable(test4 ../src/EventHandler.cpp ../src/EventHandler.hpp events_test.cpp doctest.h)

add_test(NAME dummy_test_1 COMMAND test1)
add_test(NAME dummy_test_2 COMMAND test2)
add_test(NAME Collision_test COMMAND test3)
add_test(NAME Events_test COMMAND test4)

target_link_libraries(test1 PRIVATE doctest::doctest)
target_link_libraries(test2 PRIVATE doctest::doctest)
target_link_libraries(test3 PRIVATE sfml-graphics sfml-window sfml-system doctest::doctest)
target_link_libraries(test4 PRIVATE sfml-graphics sfml-window sfml-system doctest::doctest tgui)