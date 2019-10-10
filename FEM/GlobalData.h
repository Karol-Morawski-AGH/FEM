#pragma once
#include "config.h"

#include <iostream>

class GlobalData
{
public:
	double H, W;
	uint nH, nW;
	//May be changed/removed
	uint nN, nE;
	

	GlobalData() {
		H = 0;
		W = 0;
		nH = 0;
		nW = 0;
	}

	GlobalData(double Hc, double Wc, int nHc, int nWc) {
		this->H = Hc;
		this->W = Wc;
		this->nH = nHc;
		this->nW = nWc;
		this->nN = nHc * nWc;
		this->nE = (nHc - 1) * (nWc - 1);
	}

	void print();

};

