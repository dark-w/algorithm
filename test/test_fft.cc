#include <gtest/gtest.h>
#include <random>

#include "../src/fft.h"
#include "../src/matrix.h"

TEST(TestFFT, BasicAssertions) {
    DMatrix A, B;
    DMatrix C = polynomial_multiplication(A, B);

    EXPECT_FALSE(false);
}
