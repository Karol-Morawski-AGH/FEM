#pragma once
#include "config.h"
#include<iostream>

class Node
{
	uint id;
	double t, x, y;
	bool bc;

public:

	/*Constructors*/
	Node();
	Node(double x, double y, double temp, bool bc);

	/*Print node info*/
	void print();
	void modify_test(double x) {
		this->x = x;
	}

	bool getBC();
	double getX();
	double getY();
	double getTemp();
	uint getId();
	void setId(uint);
};

