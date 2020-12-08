#pragma once

#include <vector>
#include <string>


using namespace std;

class InputParser
{
public:
	static vector<string> GetStrings(string fileName);
	static vector<int> GetInts(string fileName);
};

