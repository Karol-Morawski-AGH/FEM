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
	double *** surface_shape_vals;				

	IntegrationPoint* pc;						/*Integration points*/
	double* pc_w;								/*Wagi tego u góry*/

public:
	UniversalElement(uint nodeq, uint ipoint);
	void print();

	/*Getters and setters*/
	double** getKsiMatrix() { return ksi_array; }
	double** getEtaMatrix() { return eta_array; }
	double** getSVMatrix()  { return  shape_vals; }
	double*** getSSVMatrix() { return surface_shape_vals; }
};