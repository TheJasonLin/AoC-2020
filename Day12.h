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
	string source;

	Instruction(string in);
};

class Waypoint
{
public:
	int x;
	int y;
	Waypoint(int x, int y):
		x(x),
		y(y)
	{}

	void Apply(Instruction i, int xRel, int yRel);
	static int GetCounterClockwiseAngle(Instruction i);
	void ApplyAngle(int angle, int xRel, int yRel);
};

class Ferry
{
public:
	int x;
	int y;
	Waypoint waypoint;

	Ferry():
		x(0),
		y(0),
		waypoint(Waypoint(10, 1))
	{
	}

	void Apply(Instruction i);
};

class Day12
{
public:
	static void Run();
};

