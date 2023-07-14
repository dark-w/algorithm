#include "merge_sort.h"

static void __merge(std::vector<int> &v, int p, int q, int r) {
    size_t n1 = q - p + 1;
    std::vector<int> L(n1 + 1);
    for (int i = 0; i < n1; i++) {
        L[i] = v[p + i];
    }
    L[n1] = INT32_MAX;

    size_t n2 = r - q;
    std::vector<int> R(n2 + 1);
    for (int i = 0; i < n2; i++) {
        R[i] = v[q + 1 + i];
    }
    R[n2] = INT32_MAX;

    int i = 0;
    int j = 0;
    for (int k = 0; k < n1 + n2; k++) {
        if (L[i] < R[j]) {
            v[p + k] = L[i];
            i++;
        } else {
            v[p + k] = R[j];
            j++;
        }
    }
}

static void __merge_sort(std::vector<int> &v, int p, int r) {
    if (r > p) {
        int q = (p + r) / 2;
        __merge_sort(v, p, q);
        __merge_sort(v, q + 1, r);
        __merge(v, p, q, r);
    }
}

void merge_sort(std::vector<int> &v) {
    __merge_sort(v, 0, v.size() - 1);
}
