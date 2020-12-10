#pragma once
#include "Base.h"

struct Height {
	bool valid;
	bool metric;
	int value;

	Height() {}

	Height(bool metric, int value) :
		metric(metric),
		value(value)
	{
		valid = true;
	}
};

struct Passport {
	static vector<string> fields;

	string source;
	
	map<string, string> data;

	Passport(string input);

	// Bound are inclusive
	bool IsNumberValid(string key, int min, int max);

	Height GetHeight();

	bool IsHairColorValid();
	bool IsEyeColorValid();
	bool IsPassportIDValid();
};

class Day4
{
public:
	static void Run();
	static void Run2();

private:
	static vector<Passport> GetInputs();
};

