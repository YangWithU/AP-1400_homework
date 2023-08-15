#ifndef HW1_HW1_H
#define HW1_HW1_H

#include <vector>

using Matrix = std::vector<std::vector<double> >;

namespace algebra {

    Matrix zeros(std::size_t n, std::size_t m);
    Matrix ones(std::size_t n, std::size_t m);
    Matrix random(std::size_t n, std::size_t m, double min, double max);
    void show(const Matrix& matrix);
    Matrix multiply(const Matrix& matrix, double c);
}

#endif //HW1_HW1_H