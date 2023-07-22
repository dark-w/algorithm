#include "fft.h"
#include "complex.h"

#include <iostream>

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

#define PI acos(-1)

std::vector<complex> recursive_dft(const std::vector<complex>& A) {
    int n = A.size();
    if (n == 1) {
        return A;
    }

    std::vector<complex> AA(n);
    for (int i = 0; i < A.size(); i++) {
        AA[i] = A[i];
    }

    complex w(1, 0);
    complex wn;
    wn.set_r_theta(1, -2 * PI / n);

    // AA(x) = AA_even(x^2) + x * AA_odd(x^2)
    std::vector<complex> AA_even(n / 2);
    std::vector<complex> AA_odd(n / 2);
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            AA_even[i / 2] = AA[i];
        } else {
            AA_odd[i / 2] = AA[i];
        }
    }

    std::vector<complex> Y_even = recursive_dft(AA_even);
    std::vector<complex> Y_odd = recursive_dft(AA_odd);

    std::vector<complex> Y(n);
    for (int i = 0; i < n / 2; i++) {
        Y[i] = Y_even[i] + (w * Y_odd[i]);
        Y[i + (n / 2)] = Y_even[i] - (w * Y_odd[i]);

        w = w * wn;
    }

    return Y;
}

static std::vector<complex> __recursive_idft(const std::vector<complex>& Y) {
    int n = Y.size();
    if (n == 1) {
        return Y;
    }

    std::vector<complex> YY(n);
    for (int i = 0; i < Y.size(); i++) {
        YY[i] = Y[i];
    }

    complex w(1, 0);
    complex wn;
    wn.set_r_theta(1, (2 * PI) / n);

    // AA(x) = AA_even(x^2) + x * AA_odd(x^2)
    std::vector<complex> YY_even(n / 2);
    std::vector<complex> YY_odd(n / 2);
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            YY_even[i / 2] = YY[i];
        } else {
            YY_odd[i / 2] = YY[i];
        }
    }

    std::vector<complex> A_even = __recursive_idft(YY_even);
    std::vector<complex> A_odd = __recursive_idft(YY_odd);

    std::vector<complex> A(n);
    for (int i = 0; i < n / 2; i++) {
        A[i] = A_even[i] + (w * A_odd[i]);
        A[i + (n / 2)] = A_even[i] - (w * A_odd[i]);

        w = w * wn;
    }

    return A;
}

std::vector<complex> recursive_idft(const std::vector<complex>& Y) {
    int n = get_big_pow(Y.size());
    std::vector<complex> retval = __recursive_idft(Y);
    for (int i = 0; i < retval.size(); i++) {
        retval[i] = retval[i] / n;
    }
    return retval;
}

DMatrix polynomial_multiplication_fft(const DMatrix& A, const DMatrix& B) {
    int n = A.get_cols() > B.get_cols() ? A.get_cols() * 2 : B.get_cols() * 2;
    n = get_big_pow(n);

    std::vector<complex> vA(n);
    std::vector<complex> vB(n);

    for (int i = 0; i < A.get_cols(); i++) {
        vA[i] = A(0, i);
    }

    for (int i = 0; i < B.get_cols(); i++) {
        vB[i] = B(0, i);
    }

    std::vector<complex> AY = recursive_dft(vA);
    std::vector<complex> BY = recursive_dft(vB);

    // std::cout << "AY: " << std::endl;
    // for (auto c : AY) {
    //     char sign = c.get_imag() >= 0 ? '+' : '-';
    //     std::cout << c.get_real() << sign << fabs(c.get_imag()) << "i" << std::endl;
    // }
    // std::cout << std::endl;

    // std::cout << "BY: " << std::endl;
    // for (auto c : BY) {
    //     char sign = c.get_imag() >= 0 ? '+' : '-';
    //     std::cout << c.get_real() << sign << fabs(c.get_imag()) << "i" << std::endl;
    // }
    // std::cout << std::endl;

    std::vector<complex> CY(n);
    for (int i = 0; i < n; i++) {
        CY[i] = AY[i] * BY[i];
    }

    std::vector<complex> C = recursive_idft(CY);
    DMatrix R(2, n);
    for (int i = 0; i < n; i++) {
        R(0, i) = C[i].get_real();
        R(1, i) = C[i].get_imag();
    }

    return R;
}
