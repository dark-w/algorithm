#include "fib.h"
#include "matrix.h"

int fib(int n) {
    if (n <= 1) {
        return n;
    }

    return fib(n - 1) + fib(n - 2);
}

int fib_by_matrix(int n) {
    if (n <= 1) {
        return n;
    }

    DMatrix A {{1, 1}, {1, 0}};
    DMatrix x {{1}, {0}};
    DMatrix r(x);
    for (int i = 0; i < n - 1; i++) {
        r = A * r;
    }

    return r(0, 0);
}
