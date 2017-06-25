#pragma once
#include "Randomizer.h"
#include <Windows.h>
#include <iostream>
#include <tuple>
//white is unvisited, yellow is blocked, blue is on open list, red on closed, green is on path
enum Color {
	WHITE, YELLOW, BLUE, RED, GREEN, PURPLE
};
class Node {
public:
	Color color;//used to represent on console
	Node* parent;//used to track shortest path to node(can iterate back to beginning)
	int xPos; //x pos on grid
	int yPos; //y pos on grid
	int gCost; //set during alg, represents cost from start to Node
	int hCost; //found during alg, represents dist from node to end
	bool isBlocked; //for the sake of pathfinding, is node blocked
	Node(int _x, int _y);
	void Draw();//draw the node
	int fCost() const; //=g(node)+h(node)
	bool operator==(const Node& n) {
		return this->xPos == n.xPos && this->yPos == n.yPos;
	}
};

class NodeCompare {
public:
	bool operator() (const Node* n1, const Node* n2) const{
		if (n1->fCost() < n2->fCost())
			return true;
		else if (n1->fCost() == n2->fCost())
			return n1->hCost < n2->hCost;
		return false;
	}
};