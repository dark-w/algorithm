#include "fft.h"

DMatrix polynomial_multiplication(const DMatrix& A, const DMatrix& B) {
    bool is_A_bigger = A.get_cols() > B.get_cols();
    int N = is_A_bigger ? A.get_cols() * 2 : B.get_cols() * 2;

    DMatrix C(1, N);
    for (int i = 0; i < B.get_cols(); i++) {
        C(0, i) = B(0, i);
    }

    DMatrix D(1, N);
    for (int i = 0; i < A.get_cols(); i++) {
        D(0, i) = A(0, i);
    }

    DMatrix E(1, N);
    for (int i = 0; i < N; i++) {
        double e = 0;
        for (int j = 0; j < i + 1; j++) {
            e += C(0, j) * D(0, i - j);
        }
        
        E(0, i) = e;
    }

    return E;
}
