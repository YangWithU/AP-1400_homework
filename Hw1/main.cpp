#include <iostream>
#include <gtest/gtest.h>
#include "hw1.h"

int main() {
    if (false) // make false to run unit tests
    {
        Matrix x = algebra::random(3, 3, 1.0, 3.0);
        algebra::show(x);
        Matrix y = algebra::random(3, 3, 1.0, 3.0);
        algebra::show(y);
        std::cout << '\n';
        auto res = algebra::sum(x, y);
        algebra::show(res);
    }
    else
    {
        ::testing::InitGoogleTest();
        std::cout << "RUNNING TESTS ..." << std::endl;
        int ret{RUN_ALL_TESTS()};
        if (!ret)
            std::cout << "<<<SUCCESS>>>" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
    return 0;
}