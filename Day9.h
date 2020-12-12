#pragma once

#include "Base.h"

class Day9
{
public:
	static void Run();

private:
	static vector<long long> GetNumbers();

	static long long FindOutlier(vector<long long> numbers);

	static void PrintContiguous(vector<long long> numbers, long long outlier);
};

