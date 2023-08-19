#include <iostream>
#include <gtest/gtest.h>
#include "hw1.h"

int main() {
    Matrix matrix = algebra::random(4, 4, 1.0, 5.0);
    algebra::show(matrix);
    std::cout << '\n';

    auto x = algebra::inverse(matrix);
    algebra::show(x);

    return 0;
}