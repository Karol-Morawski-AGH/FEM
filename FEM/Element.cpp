#include "Element.h"

Element::Element(Node *a, Node *b, Node *c, Node *d)
{
	id.push_back(a);
	id.push_back(b);
	id.push_back(c);
	id.push_back(d);
}

Node Element::getNode(int i)
{
	Node node = *id[i];
	return node;
}

uint Element::getEdgeCount()
{
	return this->edge_with_bc_count;
}

uint* Element::getEdgeList()
{
	return this->edge_bc_list;
}

uint* Element::getNodeOrder()
{
	return this->node_order;
}

void Element::setEdgeCount(uint i)
{
	this->edge_with_bc_count = i;
}

void Element::updateEdgeList(uint index, uint value)
{
	this->edge_bc_list[index] = value;
}

void Element::setNodeOrder()
{
	this->node_order[0] = this->id[0]->getId(); 
	this->node_order[1] = this->id[2]->getId();
	this->node_order[2] = this->id[3]->getId();
	this->node_order[3] = this->id[1]->getId();
}


