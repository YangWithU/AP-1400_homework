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
        std::map<int, int> mp;
        mp[114] = 514;
        for(auto x : mp) {
            if(x.first == 114) {
                x.second -= 2;
            }
        }
        std::cout << mp[114];
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