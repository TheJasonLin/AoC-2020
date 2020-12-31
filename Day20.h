#pragma once

#include "Base.h"

enum class TileEdge {
	Top,
	Bottom,
	Left,
	Right
};

class TilePos {
public:
	int x;
	int y;

	TilePos(int x, int y) :
		x(x),
		y(y)
	{}

	TilePos():
		x(0),
		y(0)
	{}
};

class Tile {
public:
	int id;
	TilePos position;
	vector<string> pixels;
	map<TileEdge, Tile*> neighbors;
	
	Tile(int id, vector<string> pixels):
		id(id),
		pixels(pixels)
	{}

	vector<string> GetBorders() const;
	string GetBorder(TileEdge edge) const;
	int GetDim() const;

	bool IsCorner() const;
	bool IsCompatible(TileEdge e, Tile* other) const;

	void Rotate();
	void Flip();

	bool Attach(Tile* t);

	bool HasSeaMonster() const;
	void EraseSeaMonsters();
	int GetRoughness() const;

	void Print() const;
private:
	bool SelfAttach(TileEdge e, Tile* t);
	void EraseMonster(int x, int y);

	bool IsSeaMonster(int x, int y) const;
	char GetChecked(int x, int y) const;
};

class Image {
public:
	vector<Tile*> tiles;
	vector<vector<Tile*>> sortedTiles;
	Tile* master;

	Image(vector<string> inputs);

	void Link();
	void Sort();
	void Stitch();

private:
	// Methods post Link
	int GetMinX() const;
	int GetMinY() const;
	int GetDim() const;
	int GetTileDim() const;
	Tile* GetTileByPosition(int x, int y);
	char GetStitchedPixel(int x, int y) const;
};

class Day20
{
public:
	static void Run();
};

