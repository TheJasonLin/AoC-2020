#include "Day8.h"


int Instruction::Run(int& acc)
{
	runCount++;
	if (operation == "acc") {
		acc += argument;
		return 1;
	}
	
	if (operation == "jmp") {
		return argument;
	}

	if (operation == "nop") {
		return 1;
	}

	return 1;
}

void Day8::Run()
{
	auto instructions = GetInstructions();

	int acc = 0;

	Instruction* currentInstruction = instructions[0];
	int currentLine = 0;
	while (currentInstruction->runCount == 0) {
		currentLine += currentInstruction->Run(acc);
		currentInstruction = instructions[currentLine];
	}
	
	cout << "final acc: " << acc << endl;
}

void Day8::Run2()
{
	int lineCount = GetInstructions().size();
	for (int i = 0; i < lineCount; i++) {
		cout << "Attempt Line: " << i << endl;
		// Create Clean Set of Instructions
		auto instructions = GetInstructions();

		// Perform Modification if applicable
		if (instructions[i]->operation == "nop") {
			instructions[i]->operation = "jmp";
		}
		else if (instructions[i]->operation == "jmp") {
			instructions[i]->operation = "nop";
		}
		else {
			continue;
		}

		// Check for Loop
		int acc = 0;
		Instruction* currentInstruction = instructions[0];
		int currentLine = 0;
		while (currentInstruction->runCount == 0) {
			currentLine += currentInstruction->Run(acc);
			if (currentLine >= lineCount) {
				cout << "final acc: " << acc << endl;
				return;
			}
			currentInstruction = instructions[currentLine];
		}
	}
}

std::vector<Instruction*> Day8::GetInstructions()
{
	auto strings = InputParser::GetStrings("8.txt");

	vector<Instruction*> out;

	static auto e = regex("^([a-z]+) (-|\\+)([0-9]+)");

	for (auto s : strings) {	
		auto operation = regex_replace(s, e, string("$1"));
		auto sign = regex_replace(s, e, string("$2"));
		auto valueStr = regex_replace(s, e, string("$3"));
	
		auto unsignedValue = stoi(valueStr);
		auto value = sign == "+" ? unsignedValue : (-1) * unsignedValue;

		auto i = new Instruction(operation, value);
		out.push_back(i);
	}

	return out;
}
