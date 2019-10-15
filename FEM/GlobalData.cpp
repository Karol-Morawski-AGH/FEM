#include "GlobalData.h"

GlobalData::GlobalData() {
	this->H = this->W = 1;
	this->nH = this->nW = 2;
	this->nN = this->nH * this->nW;
	this->nE = (this->nH - 1) * (this->nW - 1);
	std::cout << "GlobalData has not been loaded, setting default values" << std::endl;
}

GlobalData::GlobalData(double Hc, double Wc, int nHc, int nWc) {
	if (Hc == 0 || Wc == 0 || nHc == 0 || nWc == 0) {
		std::cout << "GlobalData loaded with incorrect values, check input" << std::endl;
		exit(-1);
	}
	this->H = Hc;
	this->W = Wc;
	this->nH = nHc;
	this->nW = nWc;
	this->nN = nHc * nWc;
	this->nE = (nHc - 1) * (nWc - 1);
}

void GlobalData::print()
{
	std::cout << "H\t->\t" << this->H << std::endl << "W\t->\t" << this->W << std::endl << "nH\t->\t" << this->nH << std::endl << "nW\t->\t" << this->nW << std::endl << "nN\t->\t" << this->nN << std::endl << "nE\t->\t" << this->nE << std::endl;
}
