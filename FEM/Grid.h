#pragma once
#include "config.h"
#include "Node.h"
#include "Element.h"
#include "GlobalData.h"
#include<iostream>
#include<vector>

class Grid
{
	std::vector<Node*> nodes;
	std::vector<Element*> elements;

public:
	Grid(GlobalData data);
	Grid();
	~Grid();

	void print_nodes();
	void print_elements();
	Element* getElement(int id);
	void set_boundary_cond();
};

