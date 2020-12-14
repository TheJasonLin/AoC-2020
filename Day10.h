#pragma once

#include "Base.h"

class Adapter
{
public:
	int jolts;
	vector<Adapter*> children;
	long long cachedArragements;

	Adapter(int jolts):
		jolts(jolts)
	{
		cachedArragements = -1;
	}

	void InitChildren(map<int, Adapter*> Adapters);
	long long GetArrangements();
};

class Bag
{
public:
	Bag(vector<int> numbers);
	~Bag();

	long long GetArrangements() const;

private:
	Adapter* myDevice;
	map<int, Adapter*> adapters;
};

class Day10
{
public:
	static void Run();

private:
};