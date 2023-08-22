#include <iostream>
#include <gtest/gtest.h>
#include "client.h"
#include "server.h"

#include <chrono>
#include <random>


int main(int argc, char **argv)
{
    if (true) // make false to run unit-tests
    {
        std::mt19937_64 seed(std::chrono::steady_clock::now().time_since_epoch().count());
        std::uniform_int_distribution<int> gen_rand(1, 9);
        for(int i = 0; i < 5; i++) {
            std::cout << gen_rand(seed) << " ";
        }
    }
    else
    {
        ::testing::InitGoogleTest(&argc, argv);
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;   
}