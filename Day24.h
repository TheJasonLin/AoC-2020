#pragma once
#include "Base.h"

enum class HexDirection
{
	East,
	SouthEast,
	SouthWest,
	West,
	NorthWest,
	NorthEast,
};

class CubePos
{
public:
	int x;
	int y;
	int z;

	CubePos(int x, int y, int z):
		x(x),
		y(y),
		z(z)
	{}

	string GetHash() const;
	vector<CubePos> GetAdjacent() const;
};

class FlipInstruction
{
public:
	string source;
	vector<HexDirection> path;

	FlipInstruction(string input);

	CubePos GetEndOfPath();
};

class LobbyTile
{
public:
	CubePos pos;
	bool black;

	LobbyTile(CubePos pos):
		pos(pos),
		black(false)
	{}

	void Flip();
};

class Lobby
{
public:
	// key: CubePos hash, value: tile
	map<string, LobbyTile*> tiles;

	Lobby();

	void Apply(vector<FlipInstruction*> instructions);
	int GetBlackCount();

	void AddTile(LobbyTile* tile);
	LobbyTile* GetTile(const CubePos& pos);

	void Tick();
	vector<CubePos> GetPOI() const;
	int GetAdjacentBlackCount(const CubePos& p) const;
	bool IsBlack(const CubePos& pos) const;
};

class Day24
{
public:
	static void Run();

	static vector<FlipInstruction*> MakeInstructions();
};

