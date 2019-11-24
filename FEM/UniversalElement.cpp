#include "UniversalElement.h"
#include<iostream>

UniversalElement::UniversalElement(uint nodeq, uint ipoint)
{
	this->node_q = nodeq;
	this->ipoint_q = ipoint;
	
	/*Siatka MES i tak tworzy tylko elementy 4-wezlowe wiec*/
	/*macierz 4(liczba wezlow, a wiec liczba f ksztaltu)x4(liczba punktow calkowania)*/
	
	//std::cout << "Universal element init" << std::endl;


	/*Tworzenie tablic pochodnych po ksi i eta dla pkt calkowania*/
	this->ksi_array = new double* [this->node_q];
	this->eta_array = new double* [this->node_q];
	this->shape_vals = new double* [this->node_q];

	for (uint i = 0; i < this->node_q; i++) {
		this->eta_array[i] = new double[this->ipoint_q];
		this->ksi_array[i] = new double[this->ipoint_q];
		this->shape_vals[i] = new double[this->ipoint_q];
	}

	this->pc = new IntegrationPoint[this->ipoint_q];
	this->pc_w = new double[this->ipoint_q];
	
	/*Przy zalozeniu ze calkowanie dwupunktowe
	a=1/sqrt(3)
	PC1[-a,-a]
	PC2[a,-a]
	PC3[a,a]
	PC4[-a,a]
	*/

	/*hardcoded*/
	double a = 1. / sqrt(3.);
	this->pc[0].eta = -a;
	this->pc[0].ksi = -a;

	this->pc[1].eta = a;
	this->pc[1].ksi = -a;

	this->pc[2].eta = a;
	this->pc[2].ksi = a;

	this->pc[3].eta = -a;
	this->pc[3].ksi = a;
	/*hardcoded*/

	double ksi, eta;
	/*Liczenie pochodnych f ksztaltu po ksi/eta dla KAZDEGO PKT CALKOWANIA*/
	for (int i = 0; i < this->ipoint_q; i++) {
		eta = this->pc[i].eta;
		ksi = this->pc[i].ksi;

		this->shape_vals[i][0] = 0.25 * (1 - eta) * (1 - ksi);
		this->eta_array[i][0] = -0.25 * (1 - ksi);
		this->ksi_array[i][0] = -0.25 * (1 - eta);

		this->shape_vals[i][1] = 0.25 * (1 + eta) * (1 - ksi);
		this->eta_array[i][1] = -0.25 * (1 - ksi);
		this->ksi_array[i][1] = -0.25 * (1 + eta);

		this->shape_vals[i][2] = 0.25 * (1 + eta) * (1 + ksi);
		this->eta_array[i][2] = -0.25 * (1 + ksi);
		this->ksi_array[i][2] = -0.25 * (1 + eta);

		this->shape_vals[i][3] = 0.25 * (1 - eta) * (1 + ksi);
		this->eta_array[i][3] = -0.25 * (1 + ksi);
		this->ksi_array[i][3] = -0.25 * (1 - eta);
	}
}

void UniversalElement::print()
{
	//general vars
	std::cout << "Number of nodes: " << this->node_q << std::endl << "Number of integration points: " << this->ipoint_q << std::endl;
	std::cout << "Integration points array vals: " << std::endl;

	//print ipoints values
	for (int i = 0; i < this->ipoint_q; i++) {
		std::cout << "P" << i+1 << " (" << pc[i].eta << ",\t" << pc[i].ksi << ")" << std::endl;
	}
	
	//Print eta matrix
	std::cout << std::endl << "ETA matrix:" << std::endl;
	std::cout << "\t";
	for (int i = 0; i < this->ipoint_q; i++) {
		std::cout << "N" << i + 1 << "\t\t";
	}
	std::cout << std::endl;
	for (int i = 0; i < this->ipoint_q; i++) {
		std::cout << "P" << i+1  << "\t" << this->eta_array[i][0] << "\t" << this->eta_array[i][1] << "\t" << this->eta_array[i][2] << "\t" << this->eta_array[i][3]  << std::endl;
	}

	//Print ksi matrix
	std::cout << std::endl << "KSI matrix:" << std::endl;
	std::cout << "\t";
	for (int i = 0; i < this->ipoint_q; i++) {
		std::cout << "N" << i + 1 << "\t\t";
	}
	std::cout << std::endl;
	for (int i = 0; i < this->ipoint_q; i++) {
		std::cout << "P" << i + 1 << "\t" << this->ksi_array[i][0] << "\t" << this->ksi_array[i][1] << "\t" << this->ksi_array[i][2] << "\t" << this->ksi_array[i][3] << std::endl;
	}


}


