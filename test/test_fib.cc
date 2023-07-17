#include <gtest/gtest.h>
#include <random>

#include "../src/fib.h"

const static int fib_sample[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89};

TEST(TestFib, BasicAssertions) {
    for (int i = 0; i < sizeof(fib_sample) / sizeof(fib_sample[0]); i++) {
        EXPECT_EQ(fib_sample[i], fib(i));
    }
}

TEST(TestFib, BasicAssertions2) {
    for (int i = 0; i < 40; i++) {
        EXPECT_EQ(fib(i), fib_by_matrix(i));
    }
}
