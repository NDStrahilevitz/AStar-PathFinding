#include "stdafx.h"
#include "Randomizer.h"


Randomizer::Randomizer()
{
}

bool Randomizer::GenerateBool(float prob) {
	int roll = rand() % 100 + 1; 
	if (roll < prob * 100)
		return true;
	return false;
}

int Randomizer::GenerateInt(int max)
{
	return (rand() % (max+1));
}
