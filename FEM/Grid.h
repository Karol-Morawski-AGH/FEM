#pragma once
#include "config.h"
#include "Node.h"
#include "Element.h"
#include "GlobalData.h"
#include<iostream>
#include<vector>
#include "Jacobian.h"
#include "UniversalElement.h"
#include <math.h>

class Grid
{
	std::vector<Node*> nodes;
	std::vector<Element*> elements;
	std::vector<double> globalP;
	std::vector<double> globalH;

	std::vector<double> pGlobal;
	std::vector<std::vector<double>> hGlobal;
	std::vector<std::vector<double>> cGlobal;

public:
	Grid(GlobalData data);
	Grid();
	~Grid();

	void print_nodes();
	void print_elements();
	Element* getElement(int id);
	void set_boundary_cond();
	void compute(int, int, double, double, double, double, double, double);
	std::vector<Node*> getNodes() { return nodes; }
	std::vector<std::vector<double>> getHGlobal() { return this->hGlobal; }
	std::vector<double> getPGlobal() { return this->pGlobal; }
	
};

