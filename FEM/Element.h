#pragma once
#include "config.h"
#include "Node.h"
#include<iostream>
#include<vector>

//Node*(?)
class Element
{
	std::vector<Node*> id;
public:
	Element(Node *a, Node *b, Node *c, Node *d);

	void print()
	{
		for (int i = 0; i < id.size(); i++) {
			id[i]->print();
		}
	}

};

