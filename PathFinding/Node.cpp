#include "Node.h"

#define FOREGROUND_WHITE (FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN)
#define FOREGROUND_YELLOW (FOREGROUND_RED | FOREGROUND_GREEN)
#define FOREGROUND_PURPLE (FOREGROUND_RED | FOREGROUND_BLUE)
Node::Node(int _x, int _y) {
	this->parent = nullptr;
	this->xPos = _x;
	this->yPos = _y;
	this->gCost = 0;
	this->hCost = 0;
	this->isBlocked = Randomizer::GenerateBool(0.2f);
	if (!this->isBlocked)
		this->color = WHITE;
	else
		this->color = YELLOW;
}

int Node::fCost() const{
	return this->gCost + this->hCost;
}

void Node::Draw() {
	HANDLE consoleH = GetStdHandle(STD_OUTPUT_HANDLE); //used to handle color control for drawing
	Color c = this->color;
	switch (c) {
	case BLUE:
		SetConsoleTextAttribute(consoleH, FOREGROUND_BLUE);
		break;
	case RED:
		SetConsoleTextAttribute(consoleH, FOREGROUND_RED);
		break;
	case GREEN:
		SetConsoleTextAttribute(consoleH, FOREGROUND_GREEN);
		break;
	case YELLOW:
		SetConsoleTextAttribute(consoleH, FOREGROUND_YELLOW);
		break;
	case PURPLE:
		SetConsoleTextAttribute(consoleH, FOREGROUND_PURPLE);
		break;
	default:
		SetConsoleTextAttribute(consoleH, FOREGROUND_WHITE);
		break;
	}
//	if (this->fCost() != 0)
	//	std::cout << this->gCost << "|" << this->hCost << " ";
//	else
	//	std::cout << "00" << "|" << "00" << " ";
	printf("*");
	SetConsoleTextAttribute(consoleH, FOREGROUND_WHITE);
}
