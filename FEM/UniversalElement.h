#pragma once
#include "config.h"
#include "IntegrationPoint.h"
#include<vector>

class UniversalElement
{
	uint ipoint_q;								/*Number of integration points*/
	uint node_q;								/*Number of nodes in element*/

	double** ksi_array;							/*Values of the partial shape functions with respect to ksi*/
	double** eta_array;							/*Values of the partial shape functions with respect to eta*/

	double ** shape_vals;						/*Values of shape functions*/

	IntegrationPoint* pc;						/*Integration points*/
	double* pc_w;					/*Wagi tego u góry*/

public:
	UniversalElement(uint nodeq, uint ipoint);
	void print();
};