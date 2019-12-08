#include <iostream>
#include "FemMethods.h"
#include "GlobalData.h"
#include "Node.h"
#include "config.h"
#include "Element.h"
#include "Grid.h"
#include "UniversalElement.h"
#include "Jacobian.h"


//TODO project structure

//Reading and setting GlobalData
std::vector<std::vector<std::string>> input = readCSV("input.txt", '\t');
GlobalData data(std::stod(input[0][0]), std::stod(input[1][0]), std::stoul(input[2][0]), std::stoul(input[3][0]), std::stod(input[4][0]), std::stod(input[5][0]), std::stod(input[6][0]), std::stod(input[7][0]), std::stod(input[8][0]), std::stod(input[9][0]), std::stod(input[10][0]), std::stod(input[11][0]));

int main()
{
	//data.print();

	Grid* grid = new Grid(data);
	grid->compute(data.getNH(), data.getNW(), data.getSC(), data.getDensity(), data.getLambda(), data.getTimeStep());


	delete grid;
}
