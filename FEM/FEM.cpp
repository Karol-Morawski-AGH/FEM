#include <iostream>
#include "FemMethods.h"
#include "GlobalData.h"
#include "Node.h"
#include "config.h"
#include "Element.h"
#include "Grid.h"

int main()
{
	std::vector<std::vector<std::string>> input = readCSV("input.txt");

	GlobalData data(std::stod(input[1][0]), std::stod(input[1][1]), std::stoul(input[1][2]), std::stoul(input[1][3]));;
	Grid* testGrid = new Grid(data);
	//testGrid->print_nodes();
	testGrid->print_elements();

	delete testGrid;
}
