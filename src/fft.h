#pragma once

#include "matrix.h"
#include "complex.h"

DMatrix polynomial_multiplication_naive(const DMatrix& A, const DMatrix& B);
DMatrix polynomial_multiplication_karatsuba(const DMatrix& A, const DMatrix& B);

std::vector<complex> recursive_dft(const std::vector<complex>& A);
std::vector<complex> recursive_idft(const std::vector<complex>& Y);
DMatrix polynomial_multiplication_fft(const DMatrix& A, const DMatrix& B);
