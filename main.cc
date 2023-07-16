#include <iostream>

#include "src/insert_sort.h"
#include "src/matrix.h"

#include <vector>

int main() {
	DMatrix A {{1, 2, 3}, {2, 5, 6}, {1, 6, 1}};
	DMatrix b {{1, 2, 3}, {2, 5, 6}, {1, 6, 1}};

	std::cout << "L" << std::endl;
	std::cout << A.get_LU().first; 
	std::cout << "U" << std::endl;
	std::cout << A.get_LU().second;
	std::cout << "L * U" << std::endl;
	std::cout << A.get_LU().first * A.get_LU().second;

	// std::cout << A.exchange_two_rows(0, 1);
	std::cout << A.get_permutation({{1, 2}});
	std::cout << A.transpose();
	std::cout << A.get_symmetric();
	return 0;
}
