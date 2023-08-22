cmake_minimum_required(VERSION 3.13)
project(Hw2)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenSSL REQUIRED)
find_package(GTest REQUIRED)

include_directories(include/)

add_executable(Hw2
        main.cpp
        server.cpp
        client.cpp
        crypto.cpp
        unit_test.cpp
)
target_link_libraries(Hw2
        OpenSSL::SSL
        GTest::GTest
        GTest::Main
)

