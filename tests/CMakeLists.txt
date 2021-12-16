cmake_minimum_required(VERSION 3.10)

project(HoraGladiis_tests VERSION 0.0.1 LANGUAGES CXX)

include(CTest)

find_package(doctest REQUIRED)

add_executable(test1 test1.cpp doctest.h)
add_executable(test2 test2.cpp doctest.h)

add_test(NAME test1 COMMAND test1)
add_test(NAME test2 COMMAND test2)

target_compile_features(test1 PRIVATE cxx_std_17)
target_link_libraries(test1 PRIVATE doctest::doctest)
target_compile_features(test2 PRIVATE cxx_std_17)
target_link_libraries(test2 PRIVATE doctest::doctest)