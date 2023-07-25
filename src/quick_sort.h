#pragma

#include <vector>

enum quick_sort_type {
    normal,
    randomized
};

void quick_sort(std::vector<int>& v, quick_sort_type qsort_type);
