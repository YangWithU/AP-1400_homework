cmake_minimum_required(VERSION 3.13)
project(Hw5)

set(CMAKE_CXX_STANDARD 20)

find_package(GTest REQUIRED)

include_directories(include/)

add_executable(Hw5
        src/main.cpp
        src/unit_test.cpp
        src/espresso_based.cpp
        src/cappuccino.cpp
        src/mocha.cpp
)
target_link_libraries(Hw5
        GTest::GTest
        GTest::Main
)
