#include <gtest/gtest.h>
#include <random>

#include "../src/fft.h"
#include "../src/matrix.h"

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

TEST(TestFFT, BasicAssertions) {
    int i = 0;
    while (i < test_data.size()) {
        DMatrix C = polynomial_multiplication(test_data[i], test_data[i + 1]);
        EXPECT_TRUE(C == test_results[i / 2]);
        
        // std::cout << C;
        i += 2;
    }
}
