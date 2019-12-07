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
	/*Initial temperature*/
	double mTbegin;
	/*Duration of process*/
	double mTime;
	/*Time step*/
	double mdTime;
	/*Specific heat capacity*/
	double mC;
	/*Thermal conductivity coefficent*/
	double mK;
	/*Density of material*/
	double mR;
	/*Ambient temperature*/
	double mTambient;
	/*Heat exchange coefficent*/
	double mConv;

public:
	/*Constructors*/
	GlobalData();
	GlobalData(double , double , int , int, double, 
		double, double, double, double, double, double, double);

	/*Print object info*/
	void print();

public:
    double getH() const;
    double getW() const;
    uint getNH() const;
    uint getNW() const;
    uint getNN() const;
    uint getNE() const;
	double getTemp();
	double getSC() { return this->mC; }
	double getDensity() { return this->mR; }
	double getLambda() { return this->mK; }
	double getTimeStep() { return this->mdTime; }
	

};

