#include <iostream>
#include <gtest/gtest.h>
#include "hw1.h"

int main() {
    if (true) // make false to run unit tests
    {
        Matrix matrix{{1, 2}};
        auto res = algebra::ero_swap(matrix, 0, 1);
//        std::cout << res;
        auto sz = matrix.size();
        algebra::show(res);
        std::cout << sz;
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