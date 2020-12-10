#pragma once
#include "Base.h"

struct Seat {
	int row;
	int col;
	int id;
	Seat(string input);
};

class Day5
{
public:
	static void Run();
};

