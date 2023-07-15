#include "find_max_subarray.h"

static find_max_subarray_result
__find_max_crossing_subarray(const std::vector<int> v, int p, int q, int r) {
    find_max_subarray_result retval(0, 0, 0);

    int left_max_sum = INT32_MIN;
    int left_index = q;
    for (int i = q; i >= p; i--) {
        int sum = left_max_sum + v[i];
        if (sum > left_max_sum) {
            left_max_sum = sum;
            left_index = i;
        }
    }

    int right_max_sum = INT32_MIN;
    int right_index = q + 1;
    for (int i = q + 1; i <= r; i++) {
        int sum = right_max_sum + v[i];
        if (sum > right_max_sum) {
            right_max_sum = sum;
            right_index = i;
        }
    }

    retval.begin = left_index;
    retval.end = right_index;
    retval.sum = left_max_sum + right_max_sum;
    return retval;
}

static find_max_subarray_result
__find_max_subarray(const std::vector<int> v, int p, int r) {
    if (p == r) {
        find_max_subarray_result retval(p, r, v[p]);

        return retval;
    } else {
        int q = (p + r) / 2;
        find_max_subarray_result left_result = 
            __find_max_subarray(v, p, q);
        find_max_subarray_result right_result =
            __find_max_subarray(v, q + 1, r);
        find_max_subarray_result crossing_result =
            __find_max_crossing_subarray(v, p, q, r);

        if (left_result >= right_result && left_result >= crossing_result) {
            return left_result;
        } else if (right_result >= left_result && right_result >= crossing_result) {
            return right_result;
        } else {
            return crossing_result;
        }
    }
}

find_max_subarray_result
find_max_subarray(const std::vector<int> v) {
    return __find_max_subarray(v, 0, v.size() - 1);
}
