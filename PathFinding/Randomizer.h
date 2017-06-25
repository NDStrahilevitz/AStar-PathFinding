#pragma once
#include <time.h>
#include <stdlib.h>
class Randomizer
{
public:
	Randomizer();
	static bool GenerateBool(float prob); //prob is for for probability to get a true;
	static int GenerateInt(int max); //generates a number from 0 to max
};

