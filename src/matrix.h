#pragma once

#include <Eigen/Dense>
#include <vector>

#include <iostream>

class DMatrix {
public:
	DMatrix(int rows, int cols, float init_value = 0);
	DMatrix(const DMatrix&);
	DMatrix(std::initializer_list<std::initializer_list<double>>);
	DMatrix();
    DMatrix(const Eigen::MatrixXd& matrix);

	DMatrix& operator=(const DMatrix& rhs);
	DMatrix& operator*=(const DMatrix& rhs);
	double& operator()(int x, int y);
	const double& operator()(int x, int y) const;

	int get_rows() const { return _rows; }
	int get_cols() const { return _cols; }

	DMatrix get_identity() const;
	DMatrix get_permutation(std::initializer_list<std::pair<int, int>>) const;
	DMatrix get_symmetric() const;
	DMatrix get_rank() const;
	DMatrix get_rref() const; // reduced rows echelon form of A
	DMatrix get_nullspace_base() const;
	DMatrix get_inverse_by_Guass_Jordan_elimination() const;
	std::pair<DMatrix, DMatrix> get_LU() const;

	DMatrix& exchange_two_rows(int, int);
	DMatrix& transpose();

	friend std::ostream& operator<<(std::ostream& out, const DMatrix& m);
	friend DMatrix solve(const DMatrix& A, const DMatrix& X);
    friend bool operator==(const DMatrix&, const Eigen::MatrixXd&);

	~DMatrix() {
		for (int i = 0; i < _rows; i++)
			delete[] _data[i];
		
		delete[] _data;
	}

private:
	int _rows;
	int _cols;
	double** _data;
};

std::ostream& operator<<(std::ostream& out, const DMatrix& m);
DMatrix operator*(const DMatrix&, const DMatrix&);
bool operator==(const DMatrix&, const Eigen::MatrixXd&);

DMatrix solve(const DMatrix& A, const DMatrix& X);

//class MatrixCompute {
//	
//};
