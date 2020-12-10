#include "Day3.h"

Map::Map(vector<string> input)
{
	for (auto row : input) {
		vector<int> mapRow;
		for (auto c : row) {
			if (c == '#') {
				mapRow.push_back(1);
			}
			else {
				mapRow.push_back(0);
			}
		}
		Tile.push_back(mapRow);
	}
}

bool Map::IsTree(Position p)
{
	if (p.row >= Tile.size()) {
		return 0;
	}
	int normalizedColumn = p.col % Tile[0].size();

	return Tile[p.row][normalizedColumn];
}

int Map::GetFreedomRow()
{
	return Tile.size();
}

int Day3::GetTreeCountForSlope(int row, int col)
{
	auto input = InputParser::GetStrings("day3.txt");
	auto map = Map(input);

	int treeCount = 0;

	auto current = Position(0, 0);
	while (current.row < map.GetFreedomRow()) {
		treeCount += map.IsTree(current);
		current = GetOffset(current, row, col);
	}

	cout << treeCount << endl;
	return treeCount;
}

void Day3::Run2()
{
	long long product = 1;
	product *= GetTreeCountForSlope(1, 1);
	product *= GetTreeCountForSlope(1, 3);
	product *= GetTreeCountForSlope(1, 5);
	product *= GetTreeCountForSlope(1, 7);
	product *= GetTreeCountForSlope(2, 1);
	cout << product << endl;
}

Position Day3::GetOffset(Position p, int r, int c)
{
	return Position(p.row + r, p.col + c);
}
