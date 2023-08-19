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
        //std::cout << std::fixed << std::setprecision(3);
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
        Matrix res(matrix1.size(), std::vector<double>(matrix2[0].size()));
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

    inline void rowMuiltiply(Matrix& matrix, int row, double scalar) {
        for(auto &cur : matrix[row]) {
            cur *= scalar;
        }
    }

    inline void rowAdd(Matrix& matrix, int row1, int row2, double scalar) {
        for(int i = 0; i < matrix[row1].size(); i++) {
            matrix[row1][i] += matrix[row2][i] * scalar;
        }
    }

    Matrix inverse(const Matrix& matrix) {
        Matrix res(matrix), identity;
        if (matrix.size() != matrix[0].size()) {
            return Matrix{};
        }

        auto n_size = matrix.size();
        identity = createIdentity(n_size);

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
            swapRows(res, i, mxRow);
            swapRows(identity, i, mxRow);

            // 3.shrink current row
            auto scalar = res[i][i];
            rowMuiltiply(res, i, 1.0 / scalar);
            rowMuiltiply(identity, i, 1.0 / scalar);

            // 4.add
            for (int j = 0; j < n_size; j++) {
                if (j != i) {
                    auto multer = -matrix[j][i];
                    rowAdd(res, j, i, multer);
                    rowAdd(identity, j, i, multer);
                }
            }
        }
        return identity;
    }

}