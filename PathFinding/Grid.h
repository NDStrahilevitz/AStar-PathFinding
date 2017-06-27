#pragma once
#include "Node.h"
#include <vector>

class Grid{
private:
	int sizeY;
	int sizeX;
	HANDLE console;
	void cls(HANDLE hConsole);
public:
	Grid(int _x, int _y);
	std::vector< std::vector<Node*> > grid; //stores the node grid
	std::vector<Node*> GetNeighbours(Node* n);
	void Draw(); //draw the grid
};

