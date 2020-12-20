#pragma once

#include "Base.h"

struct Point
{
public:
	int x;
	int y;
	int z;
	int w;

	Point(int x, int y, int z, int w):
		x(x),
		y(y),
		z(z),
		w(w)
	{}
	Point()
	{}

	string GetHash() const;
	vector<Point> GetNeighbors() const;
};

struct AdaptiveRange
{
	int min;
	int max;
	AdaptiveRange():
		min(0),
		max(0)
	{}
	void Fit(int value);
};

class SparseGrid
{
public:
	AdaptiveRange xRange;
	AdaptiveRange yRange;
	AdaptiveRange zRange;
	AdaptiveRange wRange;

	map<string, Point> actives;

	SparseGrid(vector<string> input);
	SparseGrid() {};

	bool IsActive(const Point& p) const;
	void SetActive(Point p, bool active);
	int GetActiveNeighborCount(const Point& p) const;
};

class Day17
{
public:
	static void Run();

	static SparseGrid Cycle(const SparseGrid& g);
	static bool IsCycledActive(const SparseGrid& g, const Point& p);
};

