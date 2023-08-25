cmake_minimum_required(VERSION 3.13)
project(Hw4)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

include_directories(include/)

add_executable(Hw4
        main.cpp
        unit_test.cpp
)
target_link_libraries(Hw4
        GTest::GTest
        GTest::Main
)
