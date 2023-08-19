cmake_minimum_required(VERSION 3.13)
project(Hw1)

set(CMAKE_CXX_STANDARD 17)

include_directories(include/)

find_package(GTest REQUIRED)

add_executable(Hw1 main.cpp hw1.cpp unit_test.cpp)

target_link_libraries(Hw1
        GTest::GTest
        GTest::Main
)