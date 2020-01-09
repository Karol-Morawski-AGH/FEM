#pragma once
#include "config.h"
#include "Node.h"
#include<iostream>
#include<vector>

//Node*(?)
class Element
{
	std::vector<Node*> id;
	uint edge_with_bc_count = 0;
	uint edge_bc_list[2] = { 0,0 };
	uint node_order[4] = { 0,0,0,0 };
public:

	Element();
	Element(Node *a, Node *b, Node *c, Node *d);

	void print()
	{
		std::cout << "BC edge list: (" << edge_bc_list[0] << ", " << edge_bc_list[1] << ") count: " << edge_with_bc_count << std::endl;
		for (int i = 0; i < id.size(); i++) {
			id[i]->print();
		}
	}

	Node getNode(int i);
	uint getEdgeCount();
	uint* getEdgeList();
	uint* getNodeOrder();

	void setEdgeCount(uint i);
	void updateEdgeList(uint index, uint value);
	void setNodeOrder();

};

