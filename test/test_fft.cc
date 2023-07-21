#include <gtest/gtest.h>
#include <random>
#include <Eigen/Dense>

#include "../src/fft.h"
#include "../src/matrix.h"

using namespace Eigen;

const static std::vector<DMatrix> test_data = {
    DMatrix({{1, 2, 3}}),
    DMatrix({{1, 2, 3}}),

    DMatrix({{3, 0, 1, 0, 2}}),
    DMatrix({{1, 0, 1}}),
};

const static std::vector<DMatrix> test_results = {
    DMatrix({{1, 4, 10, 12, 9, 0}}),
    DMatrix({{3, 0, 4, 0, 3, 0, 2, 0, 0, 0}}),
};

TEST(TestFFT, Naive) {
    int i = 0;
    while (i < test_data.size()) {
        DMatrix C = polynomial_multiplication_naive(test_data[i], test_data[i + 1]);
        EXPECT_TRUE(C == test_results[i / 2]);
        
        // std::cout << C;
        i += 2;
    }
}

static bool polynomial_equals(const DMatrix& lhs, const DMatrix& rhs) {
    int N = lhs.get_cols() < rhs.get_cols() ? lhs.get_cols() : rhs.get_cols();
    for (int i = 0; i < N; i++) {
        if (fabs(lhs(0, i) - rhs(0, i)) > 1e-2) {
            std::cout << "lhs(0, i): " << lhs(0, i) << " rhs(0, i): " << rhs(0, i)
                << " err: " << fabs(lhs(0, i) - rhs(0, i)) << std::endl;
            return false;
        }
    }

    return true;
}

TEST(TestFFT, Karatsuba) {
    int i = 0;

    while (i < test_data.size()) {
        DMatrix C = polynomial_multiplication_karatsuba(test_data[i], test_data[i + 1]);
        EXPECT_TRUE(polynomial_equals(C, test_results[i / 2]));
        
        i += 2;
    }

    std::random_device rd;  // 用于获取真随机数种子
    std::mt19937 gen(rd()); // 使用Mersenne Twister引擎作为随机数生成器
    std::uniform_int_distribution<int> rgtor_number(1, INT8_MAX);
    for (int i = 0; i < 100; i++) {
        int n = rgtor_number(gen);
        MatrixXd A = MatrixXd::Random(1, n) * rgtor_number(gen);
        MatrixXd B = MatrixXd::Random(1, n) * rgtor_number(gen);
        
        DMatrix AA(A);
        DMatrix BB(B);
        DMatrix C = polynomial_multiplication_karatsuba(AA, BB);
        DMatrix CC = polynomial_multiplication_naive(AA, BB);

        EXPECT_TRUE(polynomial_equals(CC, C));
    }
}
