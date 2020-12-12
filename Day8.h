#pragma once

#include "Base.h"

struct Instruction
{
	string operation;
	int argument;
	int runCount;

	Instruction(string operation, int argument):
		operation(operation),
		argument(argument)
	{
		runCount = 0;
	}

	// Run returns the next line to run's offset
	int Run(int& acc);
};

class Day8
{
public:
	static void Run();
	static void Run2();

private:
	static vector<Instruction*> GetInstructions();
};

