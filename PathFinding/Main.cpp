// PathFinding.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PathFinder.h"

/*
TODO:
2. change gcost and hcost change implementations to  return an int
3. change gcost method to be parent based again
*/
int main()
{
	srand(time(NULL));
	Grid * map = new Grid(50,50);
	PathFinder pf(map,0,0,49,49);
	pf.FindPath();
	pf.RetracePath();
	map->Draw();
    return 0;
}

