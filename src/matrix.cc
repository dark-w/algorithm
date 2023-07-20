#include "matrix.h"

#include <iostream>

double EPS = 1e-2; // 1e-2

DMatrix::DMatrix(int rows, int cols, float init_value)
	: _rows(rows), _cols(cols) {
	_data = new double*[_rows];

	for (int i = 0; i < _rows; i++) {
		_data[i] = new double[_cols];
		for (int j = 0; j < _cols; j++) {
			_data[i][j] = init_value;
		}
	}
}

DMatrix::DMatrix(const DMatrix& m)
	: _rows(m._rows), _cols(m._cols) {
	_data = new double*[_rows];

	for (int i = 0; i < _rows; i++) {
		_data[i] = new double[_cols];
		for (int j = 0; j < _cols; j++) {
			_data[i][j] = m._data[i][j];
		}
	}
}

DMatrix::DMatrix()
	: _rows(1), _cols(1) {
	_data = new double*[_rows];

	for (int i = 0; i < _rows; i++) {
		_data[i] = new double[_cols];
	}
}

DMatrix::DMatrix(std::initializer_list<std::initializer_list<double>> data_list) {
	_rows = data_list.size();
	_cols = data_list.begin()->size();

	_data = new double*[_rows];

	auto itr = data_list.begin();
	for (int i = 0; i < _rows; i++, itr++) {
		_data[i] = new double[_cols];
		std::copy(itr->begin(), itr->end(), _data[i]);
	}
}

DMatrix::DMatrix(const Eigen::MatrixXd& matrix)
    : _rows(matrix.rows()),
    _cols(matrix.cols()) {
    _data = new double*[_rows];
	for (int i = 0; i < _rows; i++) {
		_data[i] = new double[_cols];
		for (int j = 0; j < _cols; j++) {
			_data[i][j] = matrix(i, j);
		}
	}
}

std::ostream& operator<<(std::ostream& out, const DMatrix& m) {
	for (int i = 0; i < m._rows; i++) {
		for (int j = 0; j < m._cols; j++) {
			out << m._data[i][j] << ' ';
		}
		out << std::endl;
	}

	return out;
}

DMatrix operator*(const DMatrix& lhs, const DMatrix& rhs) {
	DMatrix temp(lhs);
	return (temp *= rhs);
}

DMatrix& DMatrix::operator*=(const DMatrix& rhs) {
	if (rhs._rows != _cols) {
		std::cout << "rhs._rows != _cols" << std::endl;
		throw "rhs._rows != _cols";
	}

	DMatrix ret_DMatrix(_rows, rhs._cols);
	for (int i = 0; i < ret_DMatrix._rows; i++) {
		for (int j = 0; j < ret_DMatrix._cols; j++) {
			for (int k = 0; k < _cols; k++) {
				ret_DMatrix._data[i][j] += _data[i][k] * rhs._data[k][j];
			}
		}
	}

	return (*this = ret_DMatrix);
}

DMatrix& DMatrix::operator=(const DMatrix& rhs) {
	if (&rhs == this)
		return *this;

	if (_cols != rhs._cols || _rows != rhs._rows) {
		for (int i = 0; i < _rows; i++) {
			delete[] _data[i];
		}
		delete[] _data;

		_rows = rhs._rows;
		_cols = rhs._cols;
		_data = new double*[_rows];
		for (int i = 0; i < _rows; i++) {
			_data[i] = new double[_cols];
			for (int j = 0; j < _cols; j++) {
				_data[i][j] = rhs._data[i][j];
			}
		}
	}
	else {
		for (int i = 0; i < _rows; i++) {
			for (int j = 0; j < _cols; j++) {
				_data[i][j] = rhs._data[i][j];
			}
		}
	}

	return *this;
}

double& DMatrix::operator()(int x, int y) {
	return _data[x][y];
}

const double& DMatrix::operator()(int x, int y) const {
	return _data[x][y];
}

// it only works for square DMatrix
DMatrix solve(const DMatrix& A, const DMatrix& b) {
	// Guassian elimination
	DMatrix U(A);
	DMatrix B(b);

	for (int i = 0; i < U._rows; i++) {
		if (U(i, i) == 0) {
			std::cout << "pls check the A DMatrix, it looks not right." << std::endl;
			throw "pls check the A DMatrix, it looks not right.";
		}

		for (int j = i + 1; j < U._rows; j++) {
			double ec = U(j, i) / U(i, i);
			// std::cout << "ec: " << ec << std::endl;
			for (int k = i + 1; k < U._cols; k++) {
				U(j, k) = U(j, k) - ec * U(i, k);
			}

			B(j, 0) = B(j, 0) - ec * B(i, 0);
			U(j, i) = 0;
		}
	}
	// std::cout << B;

	// back substitution
	DMatrix X(A._rows, 1);
	X(A._rows - 1, 0) = B(B._rows - 1, 0) / U(A._rows - 1, A._cols - 1);
	
	for (int i = A._rows - 2; i >= 0; i--) {
		double sum = 0;
		for (int j = A._cols - 1; j > i; j--) {
			sum += X(j, 0) * U(i, j);
		}
		X(i, 0) = (B(i, 0) - sum) / U(i, i);
	}

	return X;
}

DMatrix DMatrix::get_identity() const {
	DMatrix identity_DMatrix(_rows, _rows, 0);

	for (int i = 0; i < _rows; i++) {
		identity_DMatrix(i, i) = 1;
	}

	return identity_DMatrix;
}

DMatrix& DMatrix::exchange_two_rows(int a, int b) {
	for (int i = 0; i < _cols; i++) {
		double t = (*this)(a, i);
		(*this)(a, i) = (*this)(b, i);
		(*this)(b, i) = t;
	}
	
	return *this;
}

// it only works for square DMatrix now.
DMatrix& DMatrix::transpose() {
	for (int i = 1; i < _rows; i++) {
		for (int j = 0; j < i; j++) {
			double t = (*this)(i, j);
			(*this)(i, j) = (*this)(j, i);
			(*this)(j, i) = t;
		}
	}

	return *this;
}

DMatrix 
DMatrix::get_permutation(std::initializer_list<std::pair<int, int>> indices) 
const {
	DMatrix p(get_identity());

	for (auto i : indices) {
		p.exchange_two_rows(i.first, i.second);
	}

	return p;
}

DMatrix DMatrix::get_symmetric() const {
	DMatrix symmetric_DMatrix(*this);
	return *this * symmetric_DMatrix.transpose();
}

DMatrix DMatrix::get_rank() const {
	DMatrix rank;
	return rank;
}

// reduced rows echelon form of A
DMatrix DMatrix::get_rref() const {
	DMatrix rref;
	return rref;
}

DMatrix DMatrix::get_nullspace_base() const {
	DMatrix nullspace_base;
	return nullspace_base;
}

DMatrix DMatrix::get_inverse_by_Guass_Jordan_elimination() const {
	// Guass-Jordan Enimination
	// E[AI] = [I(A^-1)]
	
	DMatrix I(this->get_identity());
	DMatrix A(*this);

	for (int i = 0; i < _rows; i++) {
		for (int j = i + 1; j < _rows; j++) {
			double ec = A(j, i) / A(i, i);
			for (int k = 0; k < _cols; k++) {
				A(j, k) = A(j, k) - ec * A(i, k);
				I(j, k) = I(j, k) - ec * I(i, k);
			}
		}
	}

	// A is U now, but i need I, so continue
	for (int i = _rows - 1; i >= 0; i--) {
		// the pivot must be one
		double pivot_to_one = A(i, i) / 1;
		for (int j = 0; j < _cols; j++) {
			A(i, j) = A(i, j) / pivot_to_one; 
			I(i, j) = I(i, j) / pivot_to_one;
		}

		for (int j = i - 1; j >= 0 ; j--) {
			double ec = A(j, i) / A(i, i);
			for (int k = 0; k < _cols; k++) {
				A(j, k) = A(j, k) - ec * A(i, k);
				I(j, k) = I(j, k) - ec * I(i, k);
			}
		}
	}

	// the pivot must be one
	double pivot_to_one = A(0, 0) / 1;
	for (int j = 0; j < _cols; j++) {
		A(0, j) = A(0, j) / pivot_to_one;
		I(0, j) = I(0, j) / pivot_to_one;
	}

	return I;
}

// it only works for square DMatrix
std::pair<DMatrix, DMatrix> DMatrix::get_LU() const {
	DMatrix L(get_identity());
	DMatrix U(_rows, _cols, 0);
	DMatrix A(*this);

	for (int i = 0; i < _rows; i++) {
		for (int j = i; j < _cols; j++) {
			U(i, j) = A(i, j);
		}

		for (int j = i + 1; j < _rows; j++) {
			L(j, i) = A(j, i) / A(i, i);
			for (int k = i + 1; k < _cols; k++) {
				A(j, k) = A(j, k) - L(j, i) * A(i, k);				
			}
		}
	}

	return {L, U};
}

bool operator==(const DMatrix& lhs, const Eigen::MatrixXd& rhs) {
    if (lhs._rows != rhs.rows() || lhs._cols != rhs.cols()) {
        std::cout << "lhs._rows: " << lhs._rows << " lhs._cols: " << lhs._cols
            << std::endl << "rhs.rows(): " << rhs.rows() << " rhs.cols()" 
            << rhs.cols() << std::endl;
        return false;
    }

    for (int i = 0; i < lhs._rows; i++) {
        for (int j = 0; j < lhs._cols; j++) {
            if (fabs(lhs(i, j) - rhs(i, j)) > EPS) {
                std::cout << "lhs(i, j): " << lhs(i, j) << " rhs(i, j): " << rhs(i, j)
                    << " " << fabs(lhs(i, j) - rhs(i, j)) << std::endl;
                return false;
            }
        }
    }
}

bool operator==(const DMatrix& lhs, const DMatrix& rhs) {
    if (lhs._rows != rhs._rows || lhs._cols != rhs._cols) {
        std::cout << "lhs._rows: " << lhs._rows << " lhs._cols: " << lhs._cols
            << std::endl << "rhs.rows(): " << rhs._rows << " rhs.cols()" 
            << rhs._cols << std::endl;
        return false;
    }

    for (int i = 0; i < lhs._rows; i++) {
        for (int j = 0; j < lhs._cols; j++) {
            if (fabs(lhs(i, j) - rhs(i, j)) > EPS) {
                std::cout << "lhs(i, j): " << lhs(i, j) << " rhs(i, j): " << rhs(i, j)
                    << " err: " << fabs(lhs(i, j) - rhs(i, j)) << std::endl;
                return false;
            }
        }
    }
}
