#pragma once

#include "Base.h"

struct Position {
	int row;
	int col;
	Position(int row, int col):
		row(row),
		col(col)
	{}
};

class Map {
public:
	Map(vector<string> input);

	bool IsTree(Position p);
	int GetFreedomRow();

private:
	vector<vector<int>> Tile;
};

class Day3
{
public:
	static int GetTreeCountForSlope(int row, int col);
	static void Run2();

private:
	static Position GetOffset(Position p, int r, int c);
};

