#pragma once

#include "matrix.h"
#include "complex.h"

DMatrix polynomial_multiplication_naive(const DMatrix& A, const DMatrix& B);
DMatrix polynomial_multiplication_karatsuba(const DMatrix& A, const DMatrix& B);

enum fft_alg_type {
    recursive_fft,
    iterative_fft
};

std::vector<complex> recursive_dft(const std::vector<complex>& A);
std::vector<complex> recursive_idft(const std::vector<complex>& Y);

unsigned int bit_reverse_copy_u32(unsigned int i);
unsigned int bit_reverse_copy_all(unsigned int i, int b);
std::vector<complex> iterative_dft(const std::vector<complex>& A);
std::vector<complex> iterative_idft(const std::vector<complex>& Y);

DMatrix polynomial_multiplication_fft(const DMatrix& A, const DMatrix& B, fft_alg_type alg_type);
