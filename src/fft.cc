#include "fft.h"

DMatrix polynomial_multiplication_naive(const DMatrix& A, const DMatrix& B) {
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

static int get_big_pow(int target) {
    int temp = target - 1;
    temp |= temp >> 1;
    temp |= temp >> 2;
    temp |= temp >> 4;
    temp |= temp >> 8;
    temp |= temp >> 16;
    return (temp < 0) ? 1 : temp + 1;
}

DMatrix polynomial_multiplication_karatsuba(const DMatrix& A, const DMatrix& B) {
    int N = A.get_cols() > B.get_cols() ? A.get_cols() : B.get_cols();
    N = get_big_pow(N);
    
    if (N == 1) {
        DMatrix R(1, 2);
        R(0, 0) = A(0, 0) * B(0, 0);
        return R;
    }

    DMatrix AA(1, N, 0);
    for (int i = 0; i < A.get_cols(); i++) {
        AA(0, i) = A(0, i);
    }

    DMatrix BB(1, N, 0);
    for (int i = 0; i < B.get_cols(); i++) {
        BB(0, i) = B(0, i);
    }


    DMatrix Al(1, N / 2, 0);
    for (int i = 0; i < N / 2; i++) {
        Al(0, i) = AA(0, i);
    }

    DMatrix Ah(1, N / 2, 0);
    for (int i = 0; i < N / 2; i++) {
        Ah(0, i) = AA(0, (N / 2) + i);
    }

    DMatrix Bl(1, N / 2, 0);
    for (int i = 0; i < N / 2; i++) {
        Bl(0, i) = BB(0, i);
    }

    DMatrix Bh(1, N / 2, 0);
    for (int i = 0; i < N / 2; i++) {
        Bh(0, i) = BB(0, (N / 2) + i);
    }

    DMatrix C = polynomial_multiplication_karatsuba(Ah, Bh);
    DMatrix D = polynomial_multiplication_karatsuba(Al, Bl);
    DMatrix E = polynomial_multiplication_karatsuba(Al + Ah, Bl + Bh);
    DMatrix F = E - D - C;

    DMatrix G(1, 2 * N);

    for (int i = 0; i < N; i++) {
        G(0, i) = D(0, i);
    }

    for (int i = 0; i < N; i++) {
        G(0, (N / 2) + i) += F(0, i);
    }

    for (int i = 0; i < N; i++) {
        G(0, N + i) += C(0, i);
    }

    return G;
}
