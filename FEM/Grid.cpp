#include "Grid.h"

Grid::Grid(GlobalData data)
{
	double H = data.getH();
	double W = data.getW();
	uint nH = data.getNH();
	uint nW = data.getNW();
	uint nN = data.getNN();
	uint nE = data.getNE();
	double mTbegin = data.getTemp();
	
	/*Creating nodes*/
	double xsegmnt = W / (nW-1);
	double ysegmnt = H / (nH-1);
	
	double xgridref = 0;
	double ygridref = 0;

	for (int x = 0; x < nW; x++) {
		xgridref = x * xsegmnt;
		for (int y = 0; y < nH; y++) {
			ygridref = y * ysegmnt;
			
			bool bc = 0;
			if (xgridref == 0 || ygridref == 0 || xgridref == W || ygridref == H)
				bc = 1;

			Node* node = new Node(xgridref, ygridref, mTbegin, bc);
			nodes.push_back(node);
		}
	}

	/*Creating elements (4 nodes per element)*/
	int k = 0;
	for (int i = 0; i < nE; i++) {

		if ((i % nH) == (nH - 1)) {
			nE++;
			continue;
		}

		Node* a = nodes[i];
		Node* b = nodes[i + 1];
		Node* c = nodes[i + nH];
		Node* d = nodes[i + nH + 1];

		//TODO
		//Na tym etapie niepoprawne BC
		Element* element = new Element(a,b,c,d);
		elements.push_back(element);

	}

	// Sets boundary condition for each element
	this->set_boundary_cond();
}

Grid::Grid()
{
}

Grid::~Grid()
{
	for (int i = 0; i < elements.size(); i++) {
		delete elements[i];
	}
}

void Grid::print_nodes()
{
	for (int i = 0; i < nodes.size(); i++) {
		std::cout << i+1 << ". ";
		nodes[i]->print();
	}
}

void Grid::print_elements()
{
	for (int i = 0; i < elements.size(); i++) {
		std::cout << "Element no." << i + 1 << ". " << std::endl;
		elements[i]->print();
		std::cout << std::endl;
	}
}

Element* Grid::getElement(int id)
{
	return elements[id];
}

void Grid::set_boundary_cond()
{
	int node_stat[4] = { 0, 0, 0, 0 };
	for (int i = 0; i < elements.size(); i++) {
		Element* element = this->getElement(i);

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
	}
}

