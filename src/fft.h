#pragma once

#include "matrix.h"

DMatrix polynomial_multiplication_naive(const DMatrix& A, const DMatrix& B);
DMatrix polynomial_multiplication_karatsuba(const DMatrix& A, const DMatrix& B);
