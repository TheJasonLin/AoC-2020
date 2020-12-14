#pragma once

#include "Base.h"

enum class FerryPositionType {
	Floor,
	EmptySeat,
	OccupiedSeat
};

class Ferry
{
public:
	Ferry(vector<string> input);

	void Tick();
	string ToString();
	int GetOccupied();

private:
	// Row x Column
	vector<vector<FerryPositionType>> Layout;

	int GetAdjacentOccupied(int row, int col) const;
	bool HasVisibleOccupied(int row, int col, function< void(int&, int&) >& getNextPosition) const;
	bool IsOccupied(int row, int col) const;
	bool IsEmpty(int row, int col) const;
	bool IsWithinBounds(int row, int col) const;

	int GetRowCount() const;
	int GetColCount() const;
};

class Day11
{
public:
	static void Run();
};

