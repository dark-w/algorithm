#include "counting_sort.h"

#include <iostream>

std::vector<int> counting_sort(const std::vector<int>& v, int k) {
    std::vector<int> c(k + 1, 0);

    for (int i = 0; i < v.size(); i++) {
        c[v[i]] = c[v[i]] + 1;
    }

    for (int i = 1; i < c.size(); i++) {
        c[i] = c[i] + c[i - 1];
    }

    std::vector<int> retval_v(v.size());
    for (int i = retval_v.size() - 1; i >= 0; i--) {
        retval_v[c[v[i]] - 1] = v[i];
        c[v[i]] = c[v[i]] - 1;
    }

    return retval_v;
}
