#pragma once

#include "Base.h"

class Instruction
{
public:
	enum class Type {
		North, South, East, West, Left, Right, Forward
	};

	Type type;
	int value;

	Instruction(string in);
	Instruction(Type type, int value):
		type(type),
		value(value)
	{}
};

class Ferry
{
public:
	int x;
	int y;
	int angle;

	Ferry() :
		x(0),
		y(0),
		angle(0)
	{ }

	void Apply(Instruction i);
	Instruction GetCardinalInstructionFromAngle(int value);
};

class Day12
{
public:
	static void Run();
};

