#include <gtest/gtest.h>
#include <random>

#include "../src/find_max_subarray.h"

static find_max_subarray_result test_find_max_subarray(const std::vector<int>& nums) {
  find_max_subarray_result result(0, 0, nums[0]);

  int current_sum = nums[0];
  int current_start = 0;

  for (int i = 1; i < nums.size(); ++i) {
    if (current_sum < 0) {
      current_sum = nums[i];
      current_start = i;
    } else {
      current_sum += nums[i];
    }

    if (current_sum > result.sum) {
      result.sum = current_sum;
      result.begin = current_start;
      result.end = i;
    }
  }

  return result;
}

const static std::vector<std::vector<int>> test_data = {
    {1, 2, 3, 0, -1, -2, -3},
    {-1, -3, 2, 3, 4, -2, -3},
    {-1, -2, -3, 0, 1, 2, 3}
};

const static std::vector<find_max_subarray_result> test_results = {
    find_max_subarray_result(0, 2, 6),
    find_max_subarray_result(2, 4, 9),
    find_max_subarray_result(4, 6, 6),
};

// Demonstrate some basic assertions.
TEST(TestFindMaxSubarray, BasicAssertions) {
    std::random_device rd;  // 用于获取真随机数种子
    std::mt19937 gen(rd()); // 使用Mersenne Twister引擎作为随机数生成器
    std::uniform_int_distribution<int> rgtor_number(INT8_MIN, INT8_MAX); // 该实例适用于较小数的处理，太大容易造成越界
    std::uniform_int_distribution<int> rgtor_cnt(0, INT32_MAX);

    for (int i = 0; i < test_data.size(); i++) {
        std::vector<int> random_vector;
        
        // 生成随机数并添加到vector中
        for (int i = 0; i < rgtor_cnt(gen); ++i) {
            int randomNumber = rgtor_number(gen);
            random_vector.push_back(randomNumber);
        }

        find_max_subarray_result fms_result = find_max_subarray(test_data[i]);
        
        EXPECT_EQ(fms_result.begin, test_results[i].begin);
        EXPECT_EQ(fms_result.end, test_results[i].end);
        EXPECT_EQ(fms_result.sum, test_results[i].sum);
    }
}
