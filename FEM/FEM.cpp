#include <iostream>
#include "FemMethods.h"
#include "GlobalData.h"
#include "config.h"

int main()
{
	std::vector<std::vector<std::string>> input = readCSV("input.txt");

	GlobalData* container = new GlobalData(std::stod(input[1][0]), std::stod(input[1][1]), std::stoul(input[1][2]), std::stoul(input[1][3]));
	container->print();



	
	
}
