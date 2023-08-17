#include <gtest/gtest.h>
#include <random>

#include "../src/scheduling.h"

static bool are_vector_equal(const std::vector<int>& vec1, const std::vector<int>& vec2) {
    if (vec1.size() != vec2.size()) {
        return false;  // 如果两个向量大小不同，则它们不相同
    }

    return std::equal(vec1.begin(), vec1.end(), vec2.begin());
}

// Demonstrate some basic assertions.
TEST(TestScheduling, BasicAssertions) {
    std::random_device rd;  // 用于获取真随机数种子
    std::mt19937 gen(rd()); // 使用Mersenne Twister引擎作为随机数生成器
    std::uniform_int_distribution<int> rgtor_number(0, 100);

    std::vector<std::vector<double>> vsm(100);

    for (int i = 0; i < vsm.size(); i++) {
        std::vector<double> sm(10);
        for (int i = 0; i < 10; i++) {
            sm[i] = rgtor_number(gen);
        }

        vsm[i] = sm;
    }

    scheduling(vsm);
}
