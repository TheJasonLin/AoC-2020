#pragma once

#include "Base.h"

class Game
{
public:
	vector<int> seeds;
	Game(vector<int> seeds):
		seeds(seeds)
	{}

	// index from 1
	int GetNumber(int n);
};

class Day15
{
public:
	static void Run();
};

