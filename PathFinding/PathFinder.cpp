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
				if (neighbour->gCost > oldGCost)
					neighbour->parent = oldParent;
			}
		//	std::set<Node*>::const_iterator openListSearcher = this->openList.find(neighbour);		
			if (std::find(this->openList.begin(),this->openList.end(), neighbour)==this->openList.end()) {
				neighbour->parent = current;
				SetGCost(neighbour);
				SetHCost(neighbour);
				this->openList.insert(neighbour);
				neighbour->color = BLUE;		
			}
		}
	}
}

void PathFinder::SetGCost(Node* n) {
	if (n->parent != nullptr) {
		//calculate distances
		int xDis = n->xPos - this->startNode->xPos;
		int yDis = n->yPos - this->startNode->yPos;
		n->gCost = static_cast<int>(sqrt(xDis*xDis + yDis*yDis)); //use pytagorean theorem to find euclidean distance from node to end as a heuristic
	}
}

void PathFinder::SetHCost(Node *n) {
	if (n->parent != nullptr) {
		//calculate distances
		int xDis = n->xPos - this->endNode->xPos; 
		int yDis = n->yPos - this->endNode->yPos;
		n->hCost = static_cast<int>(sqrt(xDis*xDis + yDis*yDis)); //use pytagorean theorem to find euclidean distance from node to end as a heuristic
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