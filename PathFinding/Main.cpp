// PathFinding.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PathFinder.h"

/*
TODO:
1. reconsider openlist data structure 
*/
int main()
{
	srand(time(NULL));
	int sizeX, sizeY, startX, startY, endX, endY;
	std::cout << "enter grid's size formatted as x y" << std::endl;
	std::cin >> sizeX >> sizeY;
	std::cout << "enter starting coordinates(use index numbering)" << std::endl;
	std::cin >> startX >> startY;
	std::cout << "enter end coordinates(use index numbering)"<<std::endl;
	std::cin >> endX >> endY;
	Grid* map = new Grid(sizeX,sizeY);
	PathFinder pf(map,startX,startY,endX,endY);
	pf.FindPath();
	pf.RetracePath();
	map->Draw();
    return 0;
}

