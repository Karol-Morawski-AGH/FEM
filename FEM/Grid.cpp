#include "Grid.h"

Grid::Grid(GlobalData data)
{
	double H = data.getH();
	double W = data.getW();
	uint nH = data.getNH();
	uint nW = data.getNW();
	uint nN = data.getNN();
	uint nE = data.getNE();

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

			Node* node = new Node(xgridref, ygridref, 0, bc);
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
		std::cout << i + 1 << ". " << std::endl;
		elements[i]->print();
		std::cout << std::endl;
	}
}

Element* Grid::getElement(int id)
{
	return elements[id];
}

