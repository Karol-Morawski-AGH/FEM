#pragma once
#include "config.h"
#include "Node.h"
#include "Element.h"
#include "GlobalData.h"
#include<iostream>
#include<vector>
#include "Jacobian.h"
#include "UniversalElement.h"

class Grid
{
	std::vector<Node*> nodes;
	std::vector<Element*> elements;
	std::vector<double> globalP;
	std::vector<double> globalH;

public:
	Grid(GlobalData data);
	Grid();
	~Grid();

	void print_nodes();
	void print_elements();
	Element* getElement(int id);
	void set_boundary_cond();
	void compute(int, int, double, double, double, double);
};

