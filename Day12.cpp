#include "Day12.h"

Instruction::Instruction(string in)
{
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
		angle += i.value;
		break;
	case Instruction::Type::Right:
		angle -= i.value;
		break;
	case Instruction::Type::Forward:
		Apply(GetCardinalInstructionFromAngle(i.value));
		break;
	default:
		throw 1;
	}
}

Instruction Ferry::GetCardinalInstructionFromAngle(int value)
{
	auto NormalizedAngle = ((angle % 360) + 360) % 360;

	Instruction::Type type;
	switch (NormalizedAngle)
	{
	case 0:
		type = Instruction::Type::East;
		break;
	case 90:
		type = Instruction::Type::North;
		break;
	case 180:
		type = Instruction::Type::West;
		break;
	case 270:
		type = Instruction::Type::South;
		break;
	default:
		throw 1;
	}

	return Instruction(type, value);
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
	}

	cout << abs(f.x) + abs(f.y) << endl;
}
