#include <gtest/gtest.h>
#include <random>

#include "../src/insert_sort.h"

static bool are_vector_equal(const std::vector<int>& vec1, const std::vector<int>& vec2) {
    if (vec1.size() != vec2.size()) {
        return false;  // 如果两个向量大小不同，则它们不相同
    }

    return std::equal(vec1.begin(), vec1.end(), vec2.begin());
}

// Demonstrate some basic assertions.
TEST(TestInsertSort, BasicAssertions) {
    std::random_device rd;  // 用于获取真随机数种子
    std::mt19937 gen(rd()); // 使用Mersenne Twister引擎作为随机数生成器
    std::uniform_int_distribution<int> rgtor_number(INT32_MIN, INT32_MAX);
    std::uniform_int_distribution<int> rgtor_cnt(0, INT32_MAX);

    for (int i = 0; i < 1000; i++) {
        std::vector<int> random_vector;
        
        // 生成随机数并添加到vector中
        for (int i = 0; i < rgtor_cnt(gen); ++i) {
            int randomNumber = rgtor_number(gen);
            random_vector.push_back(randomNumber);
        }

        std::vector<int> sorted_vector = random_vector;  // 创建新的vector并复制原始数组内容
        std::sort(sorted_vector.begin(), sorted_vector.end());  // 对新数组进行排序
        std::reverse(sorted_vector.begin(), sorted_vector.end());

        insert_sort(random_vector);
        std::cout << i << ' ';
        EXPECT_TRUE(are_vector_equal(sorted_vector, random_vector));
    }
}
