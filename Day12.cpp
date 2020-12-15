#include "Day12.h"

Instruction::Instruction(string in)
{
	source = in;
	static auto e = regex("([A-Z])([0-9]+)");

	static map<char, Type> typeMapping = {
		{ 'N', Type::North },
		{ 'E', Type::East },
		{ 'S', Type::South },
		{ 'W', Type::West },
		{ 'L', Type::Left },
		{ 'R', Type::Right },
		{ 'F', Type::Forward },
	};

	auto typeStr = regex_replace(in, e, "$1");
	auto valueStr = regex_replace(in, e, "$2");

	type = typeMapping.find(typeStr[0])->second;
	value = stoi(valueStr);
}

void Ferry::Apply(Instruction i)
{
	if (i.type != Instruction::Type::Forward) {
		waypoint.Apply(i, x, y);
		return;
	}

	x += i.value * waypoint.x;
	y += i.value * waypoint.y;
}

void Day12::Run()
{
	auto strings = InputParser::GetStrings("12.txt");

	vector<Instruction> instructions;

	for (auto s : strings) {
		Instruction i(s);
		instructions.push_back(i);
	}

	auto f = Ferry();

	for (auto i : instructions) {
		f.Apply(i);
		cout << i.source << "> Ferry: (" << f.x << ", " << f.y << ") WP: (" << f.waypoint.x << ", " << f.waypoint.y << ")" << endl;
	}

	cout << abs(f.x) + abs(f.y) << endl;
}

void Waypoint::Apply(Instruction i, int xRel, int yRel)
{
	switch (i.type)
	{
	case Instruction::Type::North:
		y += i.value;
		break;
	case Instruction::Type::East:
		x += i.value;
		break;
	case Instruction::Type::South:
		y -= i.value;
		break;
	case Instruction::Type::West:
		x -= i.value;
		break;
	case Instruction::Type::Left:
		// fallthrough
	case Instruction::Type::Right:
		ApplyAngle(GetCounterClockwiseAngle(i), xRel, yRel);
		break;
	default:
		throw 1;
	}
}

int Waypoint::GetCounterClockwiseAngle(Instruction i)
{
	auto angle = i.type == Instruction::Type::Left ? i.value : (-1) * i.value;
	return (angle + 360) % 360;
}

void Waypoint::ApplyAngle(int angle, int xRel, int yRel)
{
	int tmpX;
	// Pivot
	switch (angle)
	{
	case 0:
		break;
	case 90:
		tmpX = x;
		x = -y;
		y = tmpX;
		break;
	case 180:
		x = -x;
		y = -y;
		break;
	case 270:
		tmpX = x;
		x = y;
		y = -tmpX;
		break;
	case 360:
		break;
	default:
		throw 1;
	}
}
