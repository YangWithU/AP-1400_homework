#include "hw1.h"
#include <random>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <iostream>

namespace algebra {
    Matrix zeros(std::size_t n, std::size_t m) {
        Matrix res(n, std::vector<double>(m, 0));
        return res;
    }

    Matrix ones(std::size_t n, std::size_t m) {
        Matrix res(n, std::vector<double>(m, 1));
        return res;
    }

    /** @brief Generate a matrix with random double numbers
     * @param n size of row
     * @param m size of col
     * @param min min val of random number filled in matrix
     * @param max max val of random number filled in matrix
     *
     * firstly, create random seed, type: mt19937.
     * secondly, create a distribution to fix range ordered
     * finally, fill numbers in matrix
     *
     * @returns Matrix filled with random double numbers
     */
    Matrix random(std::size_t n, std::size_t m, double min, double max) {
        Matrix res(n, std::vector<double>(m));
        std::mt19937_64 seed(std::chrono::steady_clock::now().time_since_epoch().count());
        std::uniform_real_distribution<double> rand_num(min, max);
        std::for_each(res.begin(), res.end(), [&](auto &cur) {
            std::fill(cur.begin(), cur.end(), rand_num(seed));
        });
        return res;
    }

    void show(const Matrix& matrix) {
        std::cout << std::fixed << std::setprecision(3);
        for(auto &rows : matrix) {
            for(auto &num : rows) {
                std::cout << num << " ";
            }
            std::cout << '\n';
        }
    }

    //Matrix multiply(const Matrix)
}