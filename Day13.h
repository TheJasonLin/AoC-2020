#pragma once

#include "Base.h"

class Bus {
public:
	int id;
	Bus(int id):
		id(id)
	{}

	int GetFirstDepartureAfter(int time) const;
};

class Problem {
public:
	int earliestTime;
	vector<Bus> busses;

	Problem(vector<string> input);

	Bus GetEarliestBus() const;
	long long GetMatchingTime() const;
};

class Day13
{
public:
	static void Run();
	static void Run2();
};

