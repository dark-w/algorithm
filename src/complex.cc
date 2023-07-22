#include "complex.h"

// (a1a2 - b1b2) + (a1b2 + a2b1)i
complex operator*(const complex& lhs, const complex& rhs) {
    double real = lhs.real * rhs.real - lhs.imag * rhs.imag;
    double imag = lhs.real * rhs.imag + lhs.imag * rhs.real;
    return complex(real, imag);
}

complex operator+(const complex& lhs, const complex& rhs) {
    double real = lhs.real + rhs.real;
    double imag = lhs.imag + rhs.imag;
    return complex(real, imag);
}

complex operator-(const complex& lhs, const complex& rhs) {
    double real = lhs.real - rhs.real;
    double imag = lhs.imag - rhs.imag;
    return complex(real, imag);
}

complex operator/(const complex& lhs, double n) {
    double real = lhs.real / n;
    double imag = lhs.imag / n;
    return complex(real, imag);
}
