#pragma once
#include "Grid.h"
#include <set>
#include <unordered_map>
#include <algorithm>
#include <math.h>
class PathFinder
{
private:
	Grid* map;
	Node* startNode; //will be found in constructor by parameters
	Node* endNode;//will be found in constructor by parameters
	std::multiset<Node*,NodeCompare> openList; 
	std::unordered_map<size_t, Node*> closedList;
	inline size_t key(int x, int y) { return (y << 16) ^ x; }
public:
	PathFinder(Grid* _map, int sX, int sY, int eX, int eY);
	void FindPath();
	std::vector<Node*> RetracePath();
	void SetGCost(Node* n);
	void SetHCost(Node* n);
};


