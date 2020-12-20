#include "Day17.h"

void Day17::Run()
{
	auto input = InputParser::GetStrings("17.txt");

	SparseGrid g(input);

	for (int i = 0; i < 6; i++) {
		cout << "Generation " << i << endl;
		g = Cycle(g);
	}

	cout << g.actives.size() << endl;
}

SparseGrid Day17::Cycle(const SparseGrid& g)
{
	SparseGrid newGrid;

	map<string, Point> pointsOfInterest;
	for (auto entry : g.actives) {
		auto neighbors = entry.second.GetNeighbors();
		for (auto n : neighbors) {
			pointsOfInterest[n.GetHash()] = n;
		}
	}

	for (auto entry : pointsOfInterest) {
		auto p = entry.second;
		auto newActive = IsCycledActive(g, p);
		newGrid.SetActive(p, newActive);
	}

	return newGrid;
}

bool Day17::IsCycledActive(const SparseGrid& g, const Point& p)
{
	auto currentlyActive = g.IsActive(p);
	auto activeNeighborCount = g.GetActiveNeighborCount(p);

	if (currentlyActive) {
		return activeNeighborCount == 2 || activeNeighborCount == 3;
	}
	
	return activeNeighborCount == 3;
}

SparseGrid::SparseGrid(vector<string> input)
{
	auto rows = input.size();
	auto columns = input[0].length();
	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < columns; x++) {
			auto state = input[y][x];
			if (state == '#') {
				SetActive(Point(x, y, 0, 0), true);
			}
		}
	}
}

bool SparseGrid::IsActive(const Point& p) const
{
	auto hash = p.GetHash();
	return actives.find(hash) != actives.end();
}

void SparseGrid::SetActive(Point p, bool active)
{
	const auto& hash = p.GetHash();
	if (active) {
		actives[hash] = p;
		xRange.Fit(p.x);
		yRange.Fit(p.y);
		zRange.Fit(p.z);
		wRange.Fit(p.w);
	}
	else if (actives.find(hash) != actives.end()) {
		actives.erase(hash);
	}
}

int SparseGrid::GetActiveNeighborCount(const Point& p) const
{
	auto neighbors = p.GetNeighbors();

	int activeCount = 0;

	for (auto n : neighbors) {
		if (IsActive(n)) {
			activeCount++;
		}
	}

	return activeCount;
}

std::string Point::GetHash() const
{
	return to_string(x) + " " + to_string(y) + " " + to_string(z) + " " + to_string(w);
}

std::vector<Point> Point::GetNeighbors() const
{
	vector<Point> points;

	for (int xCur = x - 1; xCur <= x + 1; xCur++) {
		for (int yCur = y - 1; yCur <= y + 1; yCur++) {
			for (int zCur = z - 1; zCur <= z + 1; zCur++) {
				for (int wCur = w - 1; wCur <= w + 1; wCur++) {
					if (xCur == x && yCur == y && zCur == z && wCur == w) {
						continue;
					}
					points.push_back(Point(xCur, yCur, zCur, wCur));
				}
			}
		}
	}

	return points;
}

void AdaptiveRange::Fit(int value)
{
	if (value < min) {
		min = value;
	}
	else if (value > max) {
		max = value;
	}
}
