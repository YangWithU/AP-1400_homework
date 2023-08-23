cmake_minimum_required(VERSION 3.13)
project(Hw3)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

include_directories(include/)

add_executable(Hw3
        main.cpp
        bst.cpp
        unit_test.cpp
)

target_link_libraries(Hw3
        GTest::GTest
        GTest::Main
)