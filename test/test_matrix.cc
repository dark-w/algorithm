#include <Eigen/Dense>
#include <gtest/gtest.h>
#include <random>

#include "../src/matrix.h"

using namespace Eigen;

TEST(TestMergeSort, SquareMatrixMul) {
    std::random_device rd;  // 用于获取真随机数种子
    std::mt19937 gen(rd()); // 使用Mersenne Twister引擎作为随机数生成器
    std::uniform_int_distribution<int> rgtor_number(1, INT8_MAX);

    for (int i = 0; i < 1000; i++) {
        int n = rgtor_number(gen);
        MatrixXd matrix_left = MatrixXd::Random(n, n) * rgtor_number(gen);
        MatrixXd matrix_right = MatrixXd::Random(n, n) * rgtor_number(gen);
        MatrixXd matrix_mul_result_lr = matrix_left * matrix_right;
        MatrixXd matrix_mul_result_rl = matrix_right * matrix_left;
        DMatrix ml(matrix_left);
        DMatrix mr(matrix_right);
        DMatrix mlmr = ml * mr;
        DMatrix mrml = mr * ml;

        EXPECT_TRUE(mlmr == matrix_mul_result_lr);
        EXPECT_TRUE(mrml == matrix_mul_result_rl);
    }
}
