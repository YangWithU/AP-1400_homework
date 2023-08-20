#include <iostream>
#include <gtest/gtest.h>
#include "hw1.h"

int main() {
    Matrix x = algebra::random(4, 4, 1.0, 5.0);
    algebra::show(x);
    std::cout << '\n';
    auto y = algebra::random(4, 4, 1.0, 5.0);
    algebra::show(y);
    std::cout << '\n';

    y = algebra::concatenate(x, y, 1);
    algebra::show(y);

    return 0;
}