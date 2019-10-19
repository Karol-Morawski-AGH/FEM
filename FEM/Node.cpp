#include "Node.h"
#include<iomanip>

Node::Node()
{
	this->x = this->y = this->t = this->bc = 0;
}

Node::Node(double xc, double yc, double tc, bool bcc)
{
	this->x = xc;
	this->y = yc;
	this->t = tc;
	this->bc = bcc;
}

void Node::print()
{
	std::cout << std::fixed <<  std::setprecision(PRECISION_LEVEL) <<  "Node(" << this->x << "," << this->y << ")\tT = [" << this->t << "] BoundaryCondition = [" << this->bc << "]" << std::endl;
}
