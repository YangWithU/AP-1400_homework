#include <iostream>
#include <gtest/gtest.h>
#include "hw1.h"

int main() {
    if (false) // make false to run unit tests
    {
        Matrix matrix{{1, 2, 3}, {4, 7, 5}, {6, 1, 3}};
        auto res = algebra::upper_triangular(matrix);
//        std::cout << res;
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