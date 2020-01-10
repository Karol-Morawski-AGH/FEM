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
	this->id = 0;
}

void Node::print()
{
	std::cout << std::fixed <<  std::setprecision(PRECISION_LEVEL) <<  "Node[" << this->id << "] (" << this->x << "," << this->y << ")\tT = [" << this->t << "] BoundaryCondition = [" << this->bc << "]" << std::endl;
}

bool Node::getBC()
{
	return this->bc;
}

double Node::getX() {
	return this->x;
}

double Node::getY() {
	return this->y;
}

double Node::getTemp() {
	return this->t;
}

uint Node::getId()
{
	return this->id;
}

void Node::setId(uint id)
{
	this->id = id;
}

void Node::setTemp(double temp)
{
	this->t = temp;
}
