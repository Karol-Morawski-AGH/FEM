#include "Node.h"

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
	std::cout << "Node(" << this->x << "," << this->y << ") T = [" << this->t << "] BoundaryCondition = [" << this->bc << "]" << std::endl;
}
