#pragma once
#include "config.h"
#include <vector>

class UniversalElement;

class Jacobian
{
private:
	double det;
	double j_matrix[2][2];
	double j_matrix_inverted[2][2];
public:


	Jacobian(double[4], double[4], int, UniversalElement);
	void print();
};
