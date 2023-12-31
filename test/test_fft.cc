#include <gtest/gtest.h>
#include <random>
#include <eigen3/Eigen/Dense>
#include <cmath>
#include <fstream>

#include "../src/fft.h"
#include "../src/matrix.h"
#include "../src/complex.h"
#include "../src/dmath.h"

using namespace Eigen;

const static std::vector<DMatrix> test_data = {
    DMatrix({{1, 2, 3}}),
    DMatrix({{1, 2, 3}}),

    DMatrix({{3, 0, 1, 0, 2}}),
    DMatrix({{1, 0, 1}}),
};

const static std::vector<DMatrix> test_results = {
    DMatrix({{1, 4, 10, 12, 9, 0}}),
    DMatrix({{3, 0, 4, 0, 3, 0, 2, 0, 0, 0}}),
};

TEST(TestFFT, Naive) {
    int i = 0;
    while (i < test_data.size()) {
        DMatrix C = polynomial_multiplication_naive(test_data[i], test_data[i + 1]);
        EXPECT_TRUE(C == test_results[i / 2]);
        
        // std::cout << C;
        i += 2;
    }
}

static bool polynomial_equals(const DMatrix& lhs, const DMatrix& rhs) {
    int N = lhs.get_cols() < rhs.get_cols() ? lhs.get_cols() : rhs.get_cols();
    for (int i = 0; i < N; i++) {
        if (fabs(lhs(0, i) - rhs(0, i)) > 1e-2) {
            std::cout << "lhs(0, " << i << "): " << lhs(0, i) << " rhs(0, " << i << "): " << rhs(0, i)
                << " err: " << fabs(lhs(0, i) - rhs(0, i)) << std::endl;
            return false;
        }
    }

    return true;
}

TEST(TestFFT, Karatsuba) {
    int i = 0;

    while (i < test_data.size()) {
        DMatrix C = polynomial_multiplication_karatsuba(test_data[i], test_data[i + 1]);
        EXPECT_TRUE(polynomial_equals(C, test_results[i / 2]));
        
        i += 2;
    }

    std::random_device rd;  // 用于获取真随机数种子
    std::mt19937 gen(rd()); // 使用Mersenne Twister引擎作为随机数生成器
    std::uniform_int_distribution<int> rgtor_number(1, INT8_MAX);
    std::uniform_int_distribution<int> rgtor_cnt(INT16_MIN, INT16_MAX);
    
    for (int i = 0; i < 10; i++) {
        int n = rgtor_number(gen);
        MatrixXd A = MatrixXd::Random(1, n) * rgtor_cnt(gen);
        MatrixXd B = MatrixXd::Random(1, n) * rgtor_cnt(gen);
        
        DMatrix AA(A);
        DMatrix BB(B);
        DMatrix C = polynomial_multiplication_karatsuba(AA, BB);
        DMatrix CC = polynomial_multiplication_naive(AA, BB);

        EXPECT_TRUE(polynomial_equals(CC, C));
    }
}

const static std::vector<std::vector<complex>> dft_test_data = {
    std::vector<complex> {complex(1, 0), complex(2, 0), complex(3, 0), complex(0, 0),
     complex(0, 0), complex(0, 0), complex(0, 0), complex(0, 0)},

    std::vector<complex> {complex(3, 0), complex(0, 0), complex(1, 0), complex(0, 0),
     complex(2, 0), complex(0, 0), complex(0, 0), complex(0, 0)},

    std::vector<complex> {complex(1, 0), complex(0, 0), complex(1, 0), complex(0, 0)},

    std::vector<complex> {complex(1, 2), complex(2, -3), complex(1.1, 0), complex(0, 2.2)},
};

const static std::vector<std::vector<complex>> dft_test_results = {
    std::vector<complex> {complex(6, 0), complex(2.41421, -4.41421), complex(-2.00000, -2.00000),
     complex(-0.41421, 1.58579), complex(2.00000, 0), complex(-0.41421, -1.58579),
     complex(-2.00000, 2.00000), complex(2.41421, 4.41421)},

    std::vector<complex> {complex(6, 0), complex(1, -1), complex(4, 0),
     complex(1, 1), complex(6, 0), complex(1, -1),
     complex(4, 0), complex(1, 1)},

    std::vector<complex> {complex(2, 0), complex(0, 0), complex(2, 0),
     complex(0, 0)},

    std::vector<complex> {complex(4.1, 1.2), complex(-5.3, 0), complex(0.1, 2.8),
     complex(5.1, 4)},
};

// dft_test_data.size()
TEST(TestFFT, RecursiveDFT) {
    for (int i = 0; i < dft_test_data.size(); i++) {
        std::vector<complex> dft_result = recursive_dft(dft_test_data[i]);

        EXPECT_EQ(dft_result.size(), dft_test_results[i].size());
        
        for (int j = 0; j < dft_result.size(); j++) {
            EXPECT_LT(fabs(dft_result[j].get_real() - dft_test_results[i][j].get_real()), 1e-2);
            EXPECT_LT(fabs(dft_result[j].get_imag() - dft_test_results[i][j].get_imag()), 1e-2);
        }

        // std::cout << "dft_result: " << std::endl;
        // for (auto c : dft_result) {
        //     char sign = c.get_imag() >= 0 ? '+' : '-';
        //     std::cout << c.get_real() << sign << fabs(c.get_imag()) << "i" << std::endl;
        // }
        // std::cout << std::endl;
    }
}

TEST(TestFFT, RecursiveIDFT) {
    for (int i = 0; i < dft_test_data.size(); i++) {
        std::vector<complex> idft_result = recursive_idft(dft_test_results[i]);

        EXPECT_EQ(idft_result.size(), dft_test_data[i].size());
        
        for (int j = 0; j < idft_result.size(); j++) {
            EXPECT_LT(fabs(idft_result[j].get_real() - dft_test_data[i][j].get_real()), 1e-2);
            EXPECT_LT(fabs(idft_result[j].get_imag() - dft_test_data[i][j].get_imag()), 1e-2);
        }

        // std::cout << "idft_result: " << std::endl;
        // for (auto c : idft_result) {
        //     char sign = c.get_imag() >= 0 ? '+' : '-';
        //     std::cout << c.get_real() << sign << fabs(c.get_imag()) << "i" << std::endl;
        // }
        // std::cout << std::endl;
    }
}

TEST(TestFFT, RecursivePMFFT) {
    int i = 0;

    while (i < test_data.size()) {
        DMatrix C = polynomial_multiplication_fft(test_data[i], test_data[i + 1], recursive_fft);
        EXPECT_TRUE(polynomial_equals(C, test_results[i / 2]));
        
        // std::cout << C;
        i += 2;
    }

    std::random_device rd;  // 用于获取真随机数种子
    std::mt19937 gen(rd()); // 使用Mersenne Twister引擎作为随机数生成器
    std::uniform_int_distribution<int> rgtor_number(1, INT8_MAX);
    std::uniform_int_distribution<int> rgtor_cnt(INT16_MIN, INT16_MAX);
    for (int i = 0; i < 10; i++) {
        int n = rgtor_number(gen);
        MatrixXd A = MatrixXd::Random(1, n) * rgtor_cnt(gen);
        MatrixXd B = MatrixXd::Random(1, n) * rgtor_cnt(gen);
        
        DMatrix AA(A);
        DMatrix BB(B);
        DMatrix C = polynomial_multiplication_fft(AA, BB, recursive_fft);
        DMatrix CC = polynomial_multiplication_naive(AA, BB);

        EXPECT_TRUE(polynomial_equals(CC, C));
    }
}

TEST(TestFFT, IterativeDFT) {
    for (int i = 0; i < dft_test_data.size(); i++) {
        std::vector<complex> dft_result = iterative_dft(dft_test_data[i]);

        EXPECT_EQ(dft_result.size(), dft_test_results[i].size());
        
        for (int j = 0; j < dft_result.size(); j++) {
            EXPECT_LT(fabs(dft_result[j].get_real() - dft_test_results[i][j].get_real()), 1e-2);
            EXPECT_LT(fabs(dft_result[j].get_imag() - dft_test_results[i][j].get_imag()), 1e-2);
        }

        // std::cout << "dft_result: " << std::endl;
        // for (auto c : dft_result) {
        //     char sign = c.get_imag() >= 0 ? '+' : '-';
        //     std::cout << c.get_real() << sign << fabs(c.get_imag()) << "i" << std::endl;
        // }
        // std::cout << std::endl;
    }
}

TEST(TestFFT, IterativePMFFT) {
    int i = 0;

    while (i < test_data.size()) {
        DMatrix C = polynomial_multiplication_fft(test_data[i], test_data[i + 1], iterative_fft);
        EXPECT_TRUE(polynomial_equals(C, test_results[i / 2]));
        
        // std::cout << C;
        i += 2;
    }

    std::random_device rd;  // 用于获取真随机数种子
    std::mt19937 gen(rd()); // 使用Mersenne Twister引擎作为随机数生成器
    std::uniform_int_distribution<int> rgtor_number(1, INT8_MAX);
    std::uniform_int_distribution<int> rgtor_cnt(INT16_MIN, INT16_MAX);
    for (int i = 0; i < 10; i++) {
        int n = rgtor_number(gen);
        MatrixXd A = MatrixXd::Random(1, n) * rgtor_cnt(gen);
        MatrixXd B = MatrixXd::Random(1, n) * rgtor_cnt(gen);
        
        DMatrix AA(A);
        DMatrix BB(B);
        DMatrix C = polynomial_multiplication_fft(AA, BB, iterative_fft);
        DMatrix CC = polynomial_multiplication_naive(AA, BB);

        EXPECT_TRUE(polynomial_equals(CC, C));
    }
}

TEST(TestFFT, FFTOnSignal) {
    const int N = 1 << 8;
    std::vector<complex> A_time_domain(N);
    for (int i = 0; i < N; i++) {
        A_time_domain[i].set_real(1 * sin(2 * PI * i * 500 / 10000) + 0.5 * sin(2 * PI * i * 2000 / 10000));
        A_time_domain[i].set_imag(0);
    }

    std::vector<complex> A_freq_domain = iterative_dft(A_time_domain);
    
    std::ofstream ofs;
    ofs.open("dft.txt", std::ios::out);

    EXPECT_TRUE(ofs.is_open());

    for (int i = 0; i < A_freq_domain.size(); i++) {
        char sign = A_freq_domain[i].get_imag() > 0 ? '+' : '-';
        ofs << A_freq_domain[i].get_r() << sign << fabs(A_freq_domain[i].get_imag()) << 'i' << std::endl;
        // std::cout << A_freq_domain[i].get_r() << std::endl;
    }
    ofs.close();

    ofs.open("dft-src.txt", std::ios::out);
    for (int i = 0; i < A_freq_domain.size(); i++) {
        char sign = A_freq_domain[i].get_imag() > 0 ? '+' : '-';
        ofs << A_freq_domain[i].get_r() << sign << fabs(A_freq_domain[i].get_imag()) << 'i' << std::endl;
        // std::cout << A_freq_domain[i].get_r() << std::endl;
    }
    ofs.close();
}
