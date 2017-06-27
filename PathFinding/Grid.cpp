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
	this->console = GetStdHandle(STD_OUTPUT_HANDLE);
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

void Grid::cls(HANDLE hConsole)
{
	COORD coordScreen = { 0, 0 };    // home for the cursor 
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	// Get the number of character cells in the current buffer. 

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		return;
	}

	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	// Fill the entire screen with blanks.

	if (!FillConsoleOutputCharacter(hConsole,        // Handle to console screen buffer 
		(TCHAR) ' ',     // Character to write to the buffer
		dwConSize,       // Number of cells to write 
		coordScreen,     // Coordinates of first cell 
		&cCharsWritten))// Receive number of characters written
	{
		return;
	}

	// Get the current text attribute.

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		return;
	}

	// Set the buffer's attributes accordingly.

	if (!FillConsoleOutputAttribute(hConsole,         // Handle to console screen buffer 
		csbi.wAttributes, // Character attributes to use
		dwConSize,        // Number of cells to set attribute 
		coordScreen,      // Coordinates of first cell 
		&cCharsWritten)) // Receive number of characters written
	{
		return;
	}

	// Put the cursor at its home coordinates.

	SetConsoleCursorPosition(hConsole, coordScreen);
}

void Grid::Draw() {
	Sleep(1000);
	cls(console);
	for (int i = 0; i < this->sizeY; i++)
	{
		for (int j = 0; j < this->sizeX; j++)
		{
			this->grid[i][j]->Draw();
		}
		std::cout << "\n";
	}
}

