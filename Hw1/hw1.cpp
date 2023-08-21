#include "hw1.h"
#include <random>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <stdexcept>

namespace algebra {
    Matrix zeros(std::size_t n, std::size_t m) {
        Matrix res(n, std::vector<double>(m, 0.0));
        return res;
    }

    Matrix ones(std::size_t n, std::size_t m) {
        Matrix res(n, std::vector<double>(m, 1.0));
        return res;
    }

    /** @brief Generate a matrix with random double numbers
     * @param n size of row
     * @param m size of col
     * @param min min val of random number filled in matrix
     * @param max max val of random number filled in matrix
     *
     * firstly, create random seed, type: mt19937.
     * secondly, create a distribution to make range ordered
     * finally, fill the numbers into matrix
     *
     * @returns Matrix filled with random double numbers
     */
    Matrix random(std::size_t n, std::size_t m, double min, double max) {
        if(min > max) {
            throw std::logic_error("min value can not greater than max!");
        }
        Matrix res(n, std::vector<double>(m));
        std::mt19937_64 seed(std::chrono::steady_clock::now().time_since_epoch().count());
        std::uniform_real_distribution<double> rand_num(min, max);
        for(auto &rows : res) {
            for(auto &num : rows) {
                num = rand_num(seed);
            }
        }
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

    Matrix multiply(const Matrix& matrix, double c) {
        Matrix res(matrix);
        for(auto &rows : res) {
            for(auto &num : rows) {
                num = num * c;
            }
        }
        return res;
    }

    Matrix multiply(const Matrix& matrix1, const Matrix& matrix2) {
        Matrix res{};
        if(matrix1.empty() or matrix2.empty()) {
            return res;
        }
        if(matrix1[0].size() != matrix2.size()) {
            throw std::logic_error("size of two matrix error!");
        }
        res.resize(matrix1.size(), std::vector<double>(matrix2[0].size()));
        for(int i = 0; i < matrix1.size(); i++) {
            for(int j = 0; j < matrix2[0].size(); j++) {
                for(int k = 0; k < matrix1[0].size(); k++) {
                    res[i][j] += matrix1[i][k] * matrix2[k][j];
                }
            }
        }
        return res;
    }

    Matrix sum(const Matrix& matrix, double c) {
        Matrix res(matrix);
        for(auto &row : res) {
            for(auto &cur : row) {
                cur += c;
            }
        }
        return res;
    }

    Matrix sum(const Matrix& matrix1, const Matrix& matrix2) {
        Matrix res = algebra::zeros(matrix1.size(), matrix1[0].size());
        for(int i = 0; i < matrix1.size(); i++) {
            for(int j = 0; j < matrix1[0].size(); j++) {
                res[i][j] = matrix1[i][j] + matrix2[i][j];
            }
        }
        return res;
    }

    Matrix transpose(const Matrix& matrix) {
        Matrix res(matrix[0].size(), std::vector<double>(matrix.size()));
        for(int i = 0; i < matrix.size(); i++) {
            for(int j = 0; j < matrix[0].size(); j++) {
                res[j][i] = matrix[i][j];
            }
        }
        return res;
    }

    Matrix minor(const Matrix& matrix, size_t n, size_t m) {
        Matrix res(matrix.size() - 1, std::vector<double>(matrix[0].size() - 1));
        int cur_row = 0, cur_col = 0;
        for(int i = 0; i < matrix.size(); i++) {
            for(int j = 0; j < matrix[0].size(); j++) {
                if(i == n or j == m) continue;
                res[cur_row][cur_col++] = matrix[i][j];
            }
            cur_col = 0;
            if(i != n) cur_row++;
        }
        return res;
    }

    double determinant(const Matrix& matrix) {
        if(matrix.empty()) {
            return 1;
        }
        if(matrix.size() == 2) {
            return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
        }
        double res = 0;
        for(int i = 0; i < matrix[0].size(); i++) {
            res += matrix[0][i] * determinant(minor(matrix, 0, i)) * (i % 2 == 0 ? 1 : -1);
        }
        return res;
    }

    /**
     * For matrix inverse use:
     */
    namespace Inv {
        Matrix createIdentity(std::size_t size) {
            Matrix res = algebra::zeros(size, size);
            for(int i = 0; i < size; i++) {
                res[i][i] = 1.0;
            }
            return res;
        }

        inline void swapRows(Matrix& matrix, int row1, int row2) {
            std::swap(matrix[row1], matrix[row2]);
        }

        inline void rowMultiply(Matrix& matrix, int row, double scalar) {
            for(auto &cur : matrix[row]) {
                cur *= scalar;
            }
        }

        inline void rowAdd(Matrix& matrix, int row1, int row2, double scalar) {
            for(int i = 0; i < matrix[row1].size(); i++) {
                matrix[row1][i] += matrix[row2][i] * scalar;
            }
        }
    }

    Matrix inverse(const Matrix& matrix) {
        Matrix res(matrix);
        const auto n_size = matrix.size();

        if (matrix.size() != matrix[0].size()) {
            return Matrix{};
        }

        Matrix identity = Inv::createIdentity(n_size);

        // gaussian elimination
        for (int i = 0; i < n_size; i++) {
            // 1.find max row in current col
            int mxRow = i;
            for (int j = i + 1; j < n_size; j++) {
                if (std::abs(res[j][i]) > std::abs(res[mxRow][i])) {
                    mxRow = j;
                }
            }

            // 2.swap max to current row to calculate
            Inv::swapRows(res, i, mxRow);
            Inv::swapRows(identity, i, mxRow);

            // 3.shrink current row
            auto scalar = res[i][i];
            Inv::rowMultiply(res, i, 1.0 / scalar);
            Inv::rowMultiply(identity, i, 1.0 / scalar);

            // 4.add
            for (int j = 0; j < n_size; j++) {
                if (j != i) {
                    auto multer = -res[j][i];
                    Inv::rowAdd(res, j, i, multer);
                    Inv::rowAdd(identity, j, i, multer);
                }
            }
        }
        return identity;
    }

    Matrix concatenate(const Matrix& matrix1, const Matrix& matrix2, int axis) {
        Matrix res;
        if(axis == 0) {
            res = matrix1;
            res.insert(res.end(), matrix2.begin(), matrix2.end());
        } else {
            auto row = matrix1.size();
            auto col1 = matrix1[0].size(), col2 = matrix2[0].size();
            for(int i = 0; i < row; i++) {
                std::vector<double> v;
                v.reserve(col1 + col2);
                v.insert(v.end(), matrix1[i].begin(), matrix1[i].end());
                v.insert(v.end(), matrix2[i].begin(), matrix2[i].end());
                res.push_back(v);
            }
        }
        return res;
    }

    Matrix ero_swap(const Matrix& matrix, std::size_t r1, std::size_t r2) {
        Matrix res(matrix);
        std::swap(res[r1], res[r2]);
        return res;
    }

    Matrix ero_multiply(const Matrix& matrix, std::size_t r, double c) {
        Matrix res(matrix);
        for(auto &cur : res[r]) {
            cur *= c;
        }
        return res;
    }

    Matrix ero_sum(const Matrix& matrix, std::size_t r1, double c, std::size_t r2) {
        Matrix res(matrix);
        for(auto &cur : res[r1]) {
            cur *= c;
        }
        for(int i = 0; i < res[r2].size(); i++) {
            res[r2][i] += res[r1][i];
        }
        return res;
    }

    Matrix upper_triangular(const Matrix &matrix) {
        Matrix res(matrix);
        for(int i = 0; i < res.size(); i++) {
            for(int j = i + 1; j < res.size(); j++) {
                double scalar = -res[i][i];
                res = ero_sum(res, i, res[j][i] / scalar, j);
            }
        }
        return res;
    }

}