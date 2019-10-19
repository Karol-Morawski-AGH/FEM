#pragma once
#include "config.h"

#include <iostream>

class GlobalData
{
	/*Height and width of the grid*/
	double H, W;
	/*Number of nodes (horizontally and vertically)*/
	uint nH, nW;
	/*Number of nodes and elements*/
	uint nN, nE;

public:
	/*Constructors*/
	GlobalData();
	GlobalData(double Hc, double Wc, int nHc, int nWc);
	/*Print object info*/
	void print();

public:
    double getH() const;
    double getW() const;
    uint getNH() const;
    uint getNW() const;
    uint getNN() const;
    uint getNE() const;

};

