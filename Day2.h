#pragma once

#include <vector>
#include <string>

using namespace std;

struct Rule {
	int min;
	int max;
	char character;

	Rule(int min, int max, char character):
		min(min),
		max(max),
		character(character)
	{}
};

struct Input {
	Rule rule;
	string password;
	string source;

	Input(Rule rule, string password, string source) :
		rule(rule),
		password(password),
		source(source)
	{}
};
class Day2
{
public:
	static void Run1();
	static void Run2();

	static vector<Input> GetInputs();
};

