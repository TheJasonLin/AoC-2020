#pragma once
#include "Base.h"

class Computer
{
public:
	map<unsigned long long, unsigned long long> memory;
};

class Day14
{
public:
	static void Run();
	static unsigned long long GetMaskedValue(string mask, unsigned long long value);
	static vector<unsigned long long> GetMaskedAddresses(string mask, unsigned long long address);
};

