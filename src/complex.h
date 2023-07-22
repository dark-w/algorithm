#pragma once

#include <math.h>

class complex {
public:
    explicit complex(double real = 0, double imag = 0)
        : real(real), imag(imag) { }

    complex(const complex& c)
        : real(c.real), imag(c.imag) { }

    complex operator=(const complex& c) {
        real = c.real;
        imag = c.imag;

        return *this;
    }

    complex operator=(double r) {
        real = r;
        imag = 0;

        return *this;
    }

    double get_real() const {
        return real;
    }

    double get_imag() const {
        return imag;
    }

    double get_r() const {
        return sqrt(real * real + imag * imag);
    }

    double get_theta() const {
        return atan2(imag, real);
    }

    void set_r_theta(double r, double theta) {
        real = r * cos(theta);
        imag = r * sin(theta);
    }

    friend complex operator*(const complex& lhs, const complex& rhs);
    friend complex operator+(const complex& lhs, const complex& rhs);
    friend complex operator-(const complex& lhs, const complex& rhs);
    friend complex operator/(const complex& lhs, double n);

private:
    double real;
    double imag;
};

complex operator*(const complex& lhs, const complex& rhs);
complex operator+(const complex& lhs, const complex& rhs);
complex operator-(const complex& lhs, const complex& rhs);
complex operator/(const complex& lhs, double n);
