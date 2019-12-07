#pragma once
#include "config.h"
#include <vector>

class UniversalElement;

class Jacobian
{
private:
	double det;
	std::vector<std::vector<double>> j_matrix = { {.0, .0}, {.0, .0} };
	std::vector<std::vector<double>> j_matrix_inverted = { {.0, .0}, {.0, .0} };
public:


	Jacobian(double[4], double[4], int, UniversalElement);
	void print();
	std::vector<std::vector<double>> getJacobian();
	std::vector<std::vector<double>> getInvertedJacobian();
};
