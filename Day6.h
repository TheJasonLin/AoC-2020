#pragma once

#include "Base.h"

struct Person {
	string source;
	vector<char> questions;

	Person(string input);
};

struct Group {
	vector<Person> People;

	int GetUnique() const;
	int GetCommon() const;
};

class Day6
{
public:
	static void Run();
	static void Run2();

private:
	static vector<Group> GetGroups();
};

