#include "Grid.h"
#include<iomanip>
#include "config.h"

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
	uint order_tracker = 1;

	for (int x = 0; x < nW; x++) {
		xgridref = x * xsegmnt;
		for (int y = 0; y < nH; y++) {
			ygridref = y * ysegmnt;
			
			bool bc = 0;
			if (xgridref == 0 || ygridref == 0 || xgridref == W || ygridref == H)
				bc = 1;

			Node* node = new Node(xgridref, ygridref, mTbegin, bc);
			node->setId(order_tracker);
			nodes.push_back(node);
			order_tracker++;
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
		Node* b = nodes[i + nH];
		Node* c = nodes[i + nH + 1];
		Node* d = nodes[i + 1];


		//TODO
		//Na tym etapie niepoprawne BC
		Element* element = new Element(a,b,c,d);
		element->setNodeOrder();
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
		if (node_stat[3] == 1 && node_stat[0] == 1) {
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

void Grid::compute(int nH, int nW, double specificHeat, double density, double lambda, double tstep, double alfa, double t_ambient)
{
	UniversalElement* uElem = new UniversalElement(4, 4);

	/*Setting up global matrixes and vector*/

	//Global P vector
	this->pGlobal.resize(nH * nW);
	for (int i = 0; i < nH * nW; i++) {
		this->pGlobal[i] = 0.0;
	}

	//Global H matrix
	this->hGlobal.resize(nH * nW);
	for (int i = 0; i < nH * nW; i++) {
		this->hGlobal[i].resize(nH * nW);
		for (int j = 0; j < nH * nW; j++) {
			this->hGlobal[i][j] = 0.0;
		}
	}

	// Global C matrix
	this->cGlobal.resize(nH * nW);
	for (int i = 0; i < nH * nW; i++) {
		this->cGlobal[i].resize(nH * nW);
		for (int j = 0; j < nH * nW; j++) {
			this->cGlobal[i][j] = 0.0;
		}
	}

	double dNdx[4];
	double dNdy[4];
	double coordX[4];
	double coordY[4];
	double initialTemp[4];
	double tempInt = 0.;
	double det = 0.;
	//double cMatrix[4][4];

	// Iterates through each element (computing H and P)
	for (int i = 0; i < this->elements.size(); i++) {
		//Local H matrix, P vector and C matrix
		double hLocal[4][4] = { {0.,0.,0.,0.}, {0.,0.,0.,0.}, {0.,0.,0.,0.}, {0.,0.,0.,0.} };
		double hsLocal[4][4] = { {0.,0.,0.,0.}, {0.,0.,0.,0.}, {0.,0.,0.,0.}, {0.,0.,0.,0.} };
		double cLocal[4][4] = { {0.,0.,0.,0.}, {0.,0.,0.,0.}, {0.,0.,0.,0.}, {0.,0.,0.,0.} };
		double pLocal[4] = { 0.,0.,0.,0. };

		Element *localElement = this->getElement(i);

		// Gets all nodes parameters from element
		for (int j = 0; j < 4; j++) {
			Node localNode = localElement->getNode(j);
			coordX[j] = localNode.getX();
			coordY[j] = localNode.getY();
			initialTemp[j] = localNode.getTemp();
		}
		
		// Tworzy macierze jakobiego i wyznacza pochodne funkcji ksztaltu po x/y + interpolacja temp
		// J - punkt calkowania
		for (int j = 0; j < 4; j++) {
			Jacobian* jacobian = new Jacobian(coordX, coordY, j, *uElem);
			tempInt = 0.;
			for (int k = 0; k < 4; k++) {

				dNdx[k] = jacobian->getInvertedJacobian()[0][0] * uElem->getKsiMatrix()[j][k]
						+ jacobian->getInvertedJacobian()[0][1] * uElem->getEtaMatrix()[j][k];

				dNdy[k] = jacobian->getInvertedJacobian()[1][0] * uElem->getKsiMatrix()[j][k]
						+ jacobian->getInvertedJacobian()[1][1] * uElem->getEtaMatrix()[j][k];
				
				tempInt += initialTemp[k] * uElem->getSVMatrix()[k][j];
			}

				det = jacobian->getDet();

				// N x N^T
				// Calka objetosciowa do H i C
				for (int k = 0; k < 4; k++) {
					for (int l = 0; l < 4; l++) {

						// C lokalne
						cLocal[k][l] += specificHeat * density * uElem->getSVMatrix()[j][k] * uElem->getSVMatrix()[j][l] * det;
						// H lokalne
						hLocal[k][l] += lambda * (dNdx[k] * dNdx[l] + dNdy[k] * dNdy[l]) * det;
						// Pc lokalnie
						pLocal[k] += (specificHeat * density * uElem->getSVMatrix()[j][k]* uElem->getSVMatrix()[j][l] *det) / tstep * tempInt;
					}

				}

				for (int k = 0; k < 4; k++) {
					for (int l = 0; l < 4; l++) {
						if (i == 2 && k == 0 && l == 0) {
							//std::cout << pLocal[k] << std::endl;
						}
					}
				}



			}
		

		//Calka powierzchniowa do H i wektor P
		for (int n_surf = 0; n_surf < localElement->getEdgeCount(); n_surf++) {
			
			//FIXME 
			uint surface_id = localElement->getEdgeList()[n_surf];
			double edge_length, surf_det, x_cords[4], y_cords[4], shape_func[4], ksi, eta;
			// Wspolrzedne elementu skonczonego
			for (int cords = 0; cords < 4; cords++) {
				x_cords[cords] = localElement->getNode(cords).getX();
				y_cords[cords] = localElement->getNode(cords).getY();
			}

			// Obliczanie dlugosci boku
			if (surface_id == 1) {
				edge_length = sqrt(pow((x_cords[1]-x_cords[0]), 2) + pow((y_cords[1] - y_cords[0]),2));
			}
			else if (surface_id == 2) {
				edge_length = sqrt(pow((x_cords[1] - x_cords[2]), 2) + pow((y_cords[1] - y_cords[2]), 2));
			}
			else if (surface_id == 3) {
				edge_length = sqrt(pow((x_cords[2] - x_cords[3]), 2) + pow((y_cords[2] - y_cords[3]), 2));
			}
			else if (surface_id==4) {
				edge_length = sqrt(pow((x_cords[3] - x_cords[0]), 2) + pow((y_cords[3] - y_cords[0]), 2));
			}

			// lokalny wyznacznik macierzy jakobiego
			surf_det = edge_length / 2.;

			shape_func[0] = 0.;
			shape_func[1] = 0.;
			shape_func[2] = 0.;
			shape_func[3] = 0.;
			// Dla 2 pkt calkowania
			for (int i_point = 0; i_point < 2; i_point++) {
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 4; k++) {

						// mala zlozonosc cyklomatyczna
						if (surface_id == 1) {
							if (i_point == 0) {
								ksi = -1. / sqrt(3);
								eta = -1;
							}
							else {
								ksi =  1. / sqrt(3);
								eta =  -1;
							}
							// N1 + N2
							shape_func[0] = 0.25 * (1 - ksi) * (1 - eta);
							shape_func[1] = 0.25 * (1 + ksi) * (1 - eta);
							shape_func[2] = 0.;
							shape_func[3] = 0.;
						}
						else if (surface_id == 2) {
							if (i_point == 0) {
								ksi =  1;
								eta = -1. / sqrt(3);
							}
							else {
								ksi = 1;
								eta = 1. / sqrt(3);
							}
							// N2 + //N3
							shape_func[0] = 0.;
							shape_func[1] = 0.25 * (1 + ksi) * (1 - eta);
							shape_func[2] = 0.25 * (1 + ksi) * (1 + eta);
							shape_func[3] = 0.;

						}
						else if (surface_id == 3) {
							if (i_point == 0) {
								ksi = 1. / sqrt(3);
								eta = 1;
							}
							else {
								ksi = -1. / sqrt(3);
								eta = 1;
							}
							// N3 + //N4
							shape_func[0] = 0.;
							shape_func[1] = 0.;
							shape_func[2] = 0.25 * (1 + ksi) * (1 + eta);
							shape_func[3] = 0.25 * (1 - ksi) * (1 + eta);
						}
						else {
							if (i_point == 0) {
								ksi = -1;
								eta = 1. / sqrt(3);
							}
							else {
								ksi = -1;
								eta = -1. / sqrt(3);
							}
							// N4 + N1
							shape_func[0] = 0.25 * (1 - ksi) * (1 - eta);
							shape_func[1] = 0.;
							shape_func[2] = 0.;
							shape_func[3] = 0.25 * (1 - ksi) * (1 + eta);
						}

						// Macierz H po powierzchni
						hLocal[j][k] += alfa * shape_func[j] * shape_func[k] * surf_det;
					}
						pLocal[j] += alfa * shape_func[j] * surf_det * t_ambient;
				}
			}
		}

		if (i == 2) {
			for (int ia = 0; ia < 4; ia++) {
				//std::cout << pLocal[ia] << std::endl;
			}
		}

		// Agregacja
		for (int a = 0; a < 4; a++) {
			for (int b = 0; b < 4; b++) {
				// Indeks i
				uint i_index = localElement->getNodeOrder()[a]-1;
				// Indeks j
				uint j_index = localElement->getNodeOrder()[b]-1;
				// Dodanie do tablic globalnych
				// Dodawanie do H globalnej
				this->hGlobal[i_index][j_index] += hLocal[a][b];
				// Dodawanie do C globalnej
				this->cGlobal[i_index][j_index] += cLocal[a][b];
			}
			// Dodawanie do P globalnego
			this->pGlobal[localElement->getNodeOrder()[a]-1] += pLocal[a];
		}
	}

	// H + C/dT
	for (int a = 0; a < this->hGlobal.size(); a++) {
		for (int b = 0; b < this->hGlobal.size(); b++) {
			hGlobal[a][b] += cGlobal[a][b] / tstep;
		}
	}


	// Wypisywanie tablic

	if (display_global_matrixes == true) {
		std::cout << std::setprecision(2);
		std::cout << "MACIERZ H+C" << std::endl;
		for (int a = 0; a < 16; a++) {
			for (int b = 0; b < 16; b++) {
				printf("%.3f ", this->hGlobal[a][b]);
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		std::cout << "MACIERZ C" << std::endl;
		for (int a = 0; a < 16; a++) {
			for (int b = 0; b < 16; b++) {
				printf("%.3f ", this->cGlobal[a][b]);
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		std::cout << "WEKTOR P" << std::endl;
		for (int a = 0; a < 16; a++) {
			printf("%.3f ", this->pGlobal[a]);
		}
		std::cout << std::endl;
	}

}

