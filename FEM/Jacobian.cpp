#include "Jacobian.h"
#include "UniversalElement.h"
#include<iostream>


Jacobian::Jacobian(double x[4], double y[4], int intPointId, UniversalElement uElem)
{
	double** etaMatrix = uElem.getEtaMatrix();
	double** ksiMatrix = uElem.getKsiMatrix();
	
	double dxDeta = 
		  x[0] * etaMatrix[intPointId][0]
		+ x[1] * etaMatrix[intPointId][1]
		+ x[2] * etaMatrix[intPointId][2]
		+ x[3] * etaMatrix[intPointId][3];
	double dxDksi = 
		  x[0] * ksiMatrix[intPointId][0]
		+ x[1] * ksiMatrix[intPointId][1]
		+ x[2] * ksiMatrix[intPointId][2]
		+ x[3] * ksiMatrix[intPointId][3];
	double dyDeta =
		  x[0] * etaMatrix[intPointId][0]
		+ x[1] * etaMatrix[intPointId][1]
		+ x[2] * etaMatrix[intPointId][2]
		+ x[3] * etaMatrix[intPointId][3];
	double dyDksi =
		  x[0] * ksiMatrix[intPointId][0]
		+ x[1] * ksiMatrix[intPointId][1]
		+ x[2] * ksiMatrix[intPointId][2]
		+ x[3] * ksiMatrix[intPointId][3];
	
	//Setting up Jacobian
	this->j_matrix[0][0] = dxDksi;
	this->j_matrix[0][1] = dyDksi;
	this->j_matrix[1][0] = dxDeta;
	this->j_matrix[1][1] = dyDeta;

	this->det = (this->j_matrix[0][0] * this->j_matrix[1][1]) - (this->j_matrix[0][1] * this->j_matrix[1][0]);

	//Setting up inversed Jacobian
	this->j_matrix_inverted[0][0] = dyDeta/this->det;
	this->j_matrix_inverted[0][1] = -dyDksi / this->det;
	this->j_matrix_inverted[1][0] = -dxDeta / this->det;
	this->j_matrix_inverted[1][1] = dxDksi / this->det;
}

void Jacobian::print() {
	std::cout << "Jacobian: " << std::endl;
	std::cout << this->j_matrix[0][0] << " " << this->j_matrix[0][1] << "\n" << this->j_matrix[1][0] << " "  << this->j_matrix[1][1] << std::endl;

	std::cout << "Inversed Jacobian: " << std::endl;
	std::cout << this->j_matrix_inverted[0][0] << " " << this->j_matrix_inverted[0][1] << "\n" << this->j_matrix_inverted[1][0] << " " << this->j_matrix_inverted[1][1] << std::endl;

}