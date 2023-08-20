#include <iostream>
#include <gtest/gtest.h>
#include "hw1.h"

int main() {
    Matrix x = algebra::zeros(0, 0);
    algebra::show(x);
    auto ans = algebra::determinant(x);
    std::cout << ans;
    return 0;
}