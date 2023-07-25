#include "quick_sort.h"

#include <random>

static int __partition(std::vector<int>& v, int p, int r) {
    int pivot = v[r];
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (v[j] < pivot) {
            i++;
            int t = v[i];
            v[i] = v[j];
            v[j] = t;
        }
    }

    int t = v[i + 1];
    v[i + 1] = v[r];
    v[r] = t;

    return i + 1;
}

static int __randomized_partition(std::vector<int>& v, int p, int r) {
    std::random_device rd;  // 用于获取真随机数种子
    std::mt19937 gen(rd()); // 使用Mersenne Twister引擎作为随机数生成器
    std::uniform_int_distribution<int> rgtor_number(p, r);

    int privot_index = rgtor_number(gen);

    int t = v[privot_index];
    v[privot_index] = v[r];
    v[r] = t;

    return __partition(v, p, r);
}

static void __quick_sort(std::vector<int>& v, int p, int r) {
    if (p < r) {
        int q = __partition(v, p, r);
        __quick_sort(v, p, q - 1);
        __quick_sort(v, q + 1, r);
    }
}

static void __quick_sort_randomized(std::vector<int>& v, int p, int r) {
    if (p < r) {
        int q = __randomized_partition(v, p, r);
        __quick_sort(v, p, q - 1);
        __quick_sort(v, q + 1, r);
    }
}

void quick_sort(std::vector<int>& v, quick_sort_type qsort_type) {
    if (qsort_type == normal)
        __quick_sort(v, 0, v.size() - 1);
    else if (qsort_type == randomized)
        __quick_sort_randomized(v, 0, v.size() - 1);
}
