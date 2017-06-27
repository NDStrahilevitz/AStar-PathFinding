#include "stdafx.h"
#include "PathFinder.h"


PathFinder::PathFinder(Grid* _map, int sX, int sY, int eX, int eY){
	this->map = _map;
	this->startNode = this->map->grid[sY][sX];
	this->endNode = this->map->grid[eY][eX];
	this->startNode->isBlocked = false;
	this->endNode->isBlocked = false;
	this->startNode->color = PURPLE;
	this->endNode->color = PURPLE;
	this->openList.insert(startNode);
}

void PathFinder::FindPath() {
	while (!this->openList.empty()) {
		Node* current = *this->openList.begin();
		this->openList.erase(this->openList.begin());
		this->closedList[key(current->xPos, current->yPos)] = current;
		current->color = RED;
		for each (Node* neighbour in this->map->GetNeighbours(current))
		{
			if (neighbour == endNode)
			{
				endNode->parent = current;
				this->startNode->color = PURPLE;
				this->endNode->color = PURPLE;
				return;
			}
			//search for the neightbour in the closed list
			std::unordered_map<size_t, Node*>::const_iterator closedListSearcher = this->closedList.find(key(neighbour->xPos, neighbour->yPos));			
			//if is node is blocked or in closed list
			if (neighbour->isBlocked == true || closedListSearcher != this->closedList.end()) {
				continue;
			}
			//if neighbour already has a parent, new path may be better
			if (neighbour->parent != nullptr) {
				int oldGCost = neighbour->gCost;
				Node* oldParent = neighbour->parent;
				neighbour->parent = current;
				SetGCost(neighbour);
				if (neighbour->gCost > oldGCost) {
					neighbour->parent = oldParent;
					SetGCost(neighbour);
				}
			}	
			if (std::find(this->openList.begin(),this->openList.end(), neighbour)==this->openList.end()) {
				neighbour->parent = current;
				SetGCost(neighbour);
				SetHCost(neighbour);
				this->openList.insert(neighbour);
				neighbour->color = BLUE;		
			}
		}
		//map->Draw();
	}
}

void PathFinder::SetGCost(Node* n) {
	if (n->parent != nullptr) {
		int gCost = 0;
		Node* current = n;
		while (current->parent != nullptr) {
			if (current->parent->xPos != current->xPos && current->parent->yPos != current->yPos)
				gCost += 14;
			else
				gCost += 10;
			current = current->parent;
		}
		n->gCost = gCost;
	}
}

void PathFinder::SetHCost(Node *n) {
	if (n->parent != nullptr) {
		//calculate distances
		int xDis = abs(n->xPos - this->endNode->xPos); 
		int yDis = abs(n->yPos - this->endNode->yPos);
		n->hCost =  10*(xDis + yDis) + (14 - (2 * 10))*min(xDis, yDis); //due to the nature of movement hCost equals to the cost of steps that must be done
		//vertically or horizontally and saves the amount of steps that can be done diagonally
	}
}

//TODO: add retracing of path through parents
std::vector<Node*> PathFinder::RetracePath() {
	if (this->endNode->parent == nullptr)
		return {};
	std::vector<Node*> path = {};
	Node* current = this->endNode;
	while (current->parent != nullptr) {
		current->color = GREEN;
		path.push_back(current);
		current = current->parent;
	}
	return path;
}