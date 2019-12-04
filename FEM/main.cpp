#include <iostream>
#include "FemMethods.h"
#include "GlobalData.h"
#include "Node.h"
#include "config.h"
#include "Element.h"
#include "Grid.h"
#include "UniversalElement.h"


//TODO project structure

//Reading and setting GlobalData
std::vector<std::vector<std::string>> input = readCSV("input.txt", '\t');
GlobalData data(std::stod(input[0][0]), std::stod(input[1][0]), std::stoul(input[2][0]), std::stoul(input[3][0]), std::stod(input[4][0]), std::stod(input[5][0]), std::stod(input[6][0]), std::stod(input[7][0]), std::stod(input[8][0]), std::stod(input[9][0]));

int main()
{
	//data.print();

	Grid* grid = new Grid(data);
	//grid->print_nodes();
	//grid->print_elements();

	UniversalElement* uel = new UniversalElement(4, 4);
	//uel->print();
	grid->print_elements();


	//TODO
	/*
	//Macierze globalne

	//Macierze lokalne
	double H[4][4], P[4], C[4][4];
	
	//Ustalenie warunkow brzegowych
	//Dla kazdego elementu

	int node_stat[4] = { 0, 0, 0, 0 };
	for (int i = 0; i < data.getNE(); i++) {
		Element *element = grid->getElement(i);

		for (int j = 0; j < 4; j++) {
			node_stat[j] = element->getNode(j).getBC();
		}
		
		//zalozmy ze od boku dolnego counterclockwise do boku lewego
		//1-dolny, 2-prawy, 3-gorny, 4-lewy
		//bok dolny
		if (node_stat[0] == 1 && node_stat[1] == 1) {
			if (element->getEdgeCount() == 0) {
				element->updateEdgeList(0, 1);
				element->setEdgeCount(1);
			}
			else {
				element->updateEdgeList(1, 1);
				element->setEdgeCount(2);
			}
		}
		//bok prawy
		if (node_stat[1] == 1 && node_stat[2] == 1) {
			if (element->getEdgeCount() == 0) {
				element->updateEdgeList(0, 2);
				element->setEdgeCount(1);
			}
			else {
				element->updateEdgeList(1, 2);
				element->setEdgeCount(2);
			}
		}
		//bok gorny
		if (node_stat[2] == 1 && node_stat[3] == 1) {
			if (element->getEdgeCount() == 0) {
				element->updateEdgeList(0, 3);
				element->setEdgeCount(1);
			}
			else {
				element->updateEdgeList(1, 3);
				element->setEdgeCount(2);
			}
		}
		//bok lewy
		if (node_stat[3] == 1 && node_stat[4] == 1) {
			if (element->getEdgeCount() == 0) {
				element->updateEdgeList(0, 4);
				element->setEdgeCount(1);
			}
			else {
				element->updateEdgeList(1, 4);
				element->setEdgeCount(2);
			}
		}
	
		std::cout << "Edges with BC count: " << element->getEdgeCount() << std::endl;
		std::cout << "Edges List: {" << element->getEdgeList()[0] << ", " <<  element->getEdgeList()[1] << "}" << std::endl;

	}
	*/

	delete grid;
}
