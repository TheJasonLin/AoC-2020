#include "Day11.h"

Ferry::Ferry(vector<string> input)
{
	for (auto s : input) {
		vector<FerryPositionType> row;
		for (auto c : s) {
			if (c == 'L') {
				row.push_back(FerryPositionType::EmptySeat);
			}
			else if (c == '.') {
				row.push_back(FerryPositionType::Floor);
			}
			else if (c == '#') {
				row.push_back(FerryPositionType::OccupiedSeat);
			}
			else {
				throw 1;
			}
		}
		Layout.push_back(row);
	}
}

void Ferry::Tick()
{
	vector<vector<FerryPositionType>> NewLayout;

	for (int r = 0; r < GetRowCount(); r++) {
		vector<FerryPositionType> NewRow;
		for (int c = 0; c < GetColCount(); c++) {
			auto adjacentOccupied = GetAdjacentOccupied(r, c);
			if (IsEmpty(r, c) && adjacentOccupied == 0) {
				NewRow.push_back(FerryPositionType::OccupiedSeat);
			}
			else if (IsOccupied(r, c) && adjacentOccupied >= 5) {
				NewRow.push_back(FerryPositionType::EmptySeat);
			}
			else {
				NewRow.push_back(Layout[r][c]);
			}
		}
		NewLayout.push_back(NewRow);
	}

	Layout = NewLayout;
}

int Ferry::GetOccupied()
{
	int sum = 0;

	for (auto r : Layout) {
		for (auto entry : r) {
			if (entry == FerryPositionType::OccupiedSeat) {
				sum++;
			}
		}
	}
	return sum;
}

int Ferry::GetAdjacentOccupied(int row, int col) const
{
	int count = 0;
	vector<function<void(int&, int&)>> directionLambdas = {
		// Up Left
		[](int& r, int& c) { r--; c--; },
		// Up
		[](int& r, int& c) { r--; },
		// Up Right
		[](int& r, int& c) { r--; c++; },
		// Left
		[](int& r, int& c) { c--; },
		// Right
		[](int& r, int& c) { c++; },
		// Down Left
		[](int& r, int& c) { r++; c--; },
		// Down
		[](int& r, int& c) { r++; },
		// Down Right
		[](int& r, int& c) { r++; c++; },
	};

	for (auto l : directionLambdas) {
		if (HasVisibleOccupied(row, col, l)) {
			count++;
		}
	}
	return count;
}

bool Ferry::HasVisibleOccupied(int row, int col, function< void(int&, int&) >& getNextPosition) const
{
	getNextPosition(row, col);
	while (IsWithinBounds(row, col)) {
		auto Seat = Layout[row][col];
		switch (Seat)
		{
		case FerryPositionType::Floor:
			getNextPosition(row, col);
			break;
		case FerryPositionType::EmptySeat:
			return false;
		case FerryPositionType::OccupiedSeat:
			return true;
		default:
			throw 1;
		}
	}
	return false;
}

bool Ferry::IsOccupied(int row, int col) const
{
	if (!IsWithinBounds(row, col)) {
		return false;
	}

	return Layout[row][col] == FerryPositionType::OccupiedSeat;
}

bool Ferry::IsEmpty(int row, int col) const
{
	if (!IsWithinBounds(row, col)) {
		return false;
	}

	return Layout[row][col] == FerryPositionType::EmptySeat;
}

bool Ferry::IsWithinBounds(int row, int col) const
{
	if (row < 0 || row >= GetRowCount()) {
		return false;
	}

	if (col < 0 || col >= GetColCount()) {
		return false;
	}
	return true;
}

int Ferry::GetRowCount() const
{
	return Layout.size();
}

int Ferry::GetColCount() const
{
	return Layout[0].size();
}

string Ferry::ToString()
{
	string out = "";

	for (auto r : Layout) {
		for (auto entry : r) {
			if (entry == FerryPositionType::EmptySeat) {
				out += 'L';
			}
			else if (entry == FerryPositionType::Floor) {
				out += '.';
			}
			else if (entry == FerryPositionType::OccupiedSeat) {
				out += '#';
			}
			else {
				throw 1;
			}
		}
		out += '\n';
	}

	return out;
}

void Day11::Run()
{
	auto strings = InputParser::GetStrings("11.txt");

	Ferry f(strings);

	string hash = "";
	while (hash != f.ToString()) {
		hash = f.ToString();
		f.Tick();
		cout << hash << endl;
	}

	cout << f.GetOccupied() << endl;
}
