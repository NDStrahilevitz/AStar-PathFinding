#include "stdafx.h"
#include "Grid.h"

//accessing an element of the grid is as such grid[y][x]
Grid::Grid(int _x, int _y){
	this->sizeX = _x;
	this->sizeY = _y;
	for (int i = 0; i < _y; ++i)
	{
		std::vector<Node*> row;
		for (int j = 0; j < _x; ++j)
			row.push_back(new Node(j, i));
		this->grid.push_back(row);
	}
}

std::vector<Node*> Grid::GetNeighbours(Node* n) {
	std::vector<Node*> neighbours;
	for (int i = -1; i < 2; ++i) {
		for (int j = -1; j < 2; ++j) {
			if (!((n->yPos + i < 0 || n->yPos + i >= this->sizeY) || (n->xPos + j < 0 || n->xPos + j >= this->sizeX))) {
				neighbours.push_back(this->grid[n->yPos + i][n->xPos + j]);
			}
		}
	}
	return neighbours;
}

void Grid::Draw() {
	Sleep(100);
	system("cls");
	for (int i = 0; i < this->sizeY; i++)
	{
		for (int j = 0; j < this->sizeX; j++)
		{
			this->grid[i][j]->Draw();
		}
		std::cout << "\n";
	}
}

