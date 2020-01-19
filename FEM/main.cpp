#include <iostream>
#include "FemMethods.h"
#include "GlobalData.h"
#include "Node.h"
#include "config.h"
#include "Element.h"
#include "Grid.h"
#include "UniversalElement.h"
#include "Jacobian.h"
#include <iomanip>

//TODO project structure

//Reading and setting GlobalData
std::vector<std::vector<std::string>> input = readCSV("input.txt", '\t');
GlobalData data(std::stod(input[0][0]), std::stod(input[1][0]), std::stoul(input[2][0]), std::stoul(input[3][0]), std::stod(input[4][0]), std::stod(input[5][0]), std::stod(input[6][0]), std::stod(input[7][0]), std::stod(input[8][0]), std::stod(input[9][0]), std::stod(input[10][0]), std::stod(input[11][0]));

int main()
{
	Grid* grid = new Grid(data);
	// Czas procesu
	double process_time = data.getProcessTime();
	// Krok czasowy
	double time_step = data.getTimeStep();
	
	int iterator = 0;
	std::vector<double> temp;
	for (int i = 0; i < process_time; i += time_step) {

		std::cout << "\nIteration: " <<  iterator+1 << " [" << time_step*(iterator+1) << "s]\n" << std::endl;
		
		grid->compute(data.getNH(), data.getNW(), data.getSC(), data.getDensity(), data.getLambda(), data.getTimeStep(), data.getMConv(), data.getAmbientT());


		// Gaussian elimination to solve equations
		std::vector<Node*> nodes = grid->getNodes();
		temp = gaussianElimination(grid->getHGlobal(), grid->getPGlobal());

		// Setting nodes with new temp values
		for (int j = 0; j < data.getNN(); j++) {
			nodes[j]->setTemp(temp[j]);
		}

		// Temp values of each node on the grid
		uint order_tracker = 0;
		std::vector<double> local_temp;

		std::cout << std::setprecision(5);
		for (int k = 0; k < data.getNH(); k++) {
			for (int l = 0; l < data.getNW(); l++) {
				local_temp.push_back(nodes[order_tracker]->getTemp());

				// Displaying grid
				if (display_grid == true) {
					std::cout << local_temp[order_tracker] << " ";
				}
				order_tracker++;
			}
			if (display_grid == true) {
				std::cout << std::endl;
			}
		}

		// Find and print Tmax and Tmin
		double max_temp = *std::max_element(local_temp.begin(), local_temp.end());
		double min_temp = *std::min_element(local_temp.begin(), local_temp.end());
		
		std::cout << "\nmax_temp: " << max_temp << std::endl;
		std::cout << "min_temp: " << min_temp << std::endl;

		iterator++;
	}

	


	delete grid;
}
