#pragma once
#include "config.h"
#include "IntegrationPoint.h"
#include<vector>

class UniversalElement
{
	uint ipoint_q;								/*Number of integration points*/
	uint node_q;								/*Number of nodes in element*/

	std::vector<std::vector<double>> ksi_array;	/*Values of the partial shape functions with respect to ksi*/
	std::vector<std::vector<double>> eta_array;	/*Values of the partial shape functions with respect to eta*/

	std::vector<double> shape_vals;				/*Values of shape functions*/
	std::vector<double> bc_tab;					/*Boundary condition or somethign*/

	std::vector<IntegrationPoint> pc;			/*Integration points*/
	std::vector<double> pc_w;


public:
	UniversalElement();
};