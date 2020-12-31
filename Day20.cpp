#include "Day20.h"

const vector<TileEdge> allTileEdges = {
	TileEdge::Top,
	TileEdge::Bottom,
	TileEdge::Left,
	TileEdge::Right,
};

const vector<string> seaMonster = {
	"                  # ",
	"#    ##    ##    ###",
	" #  #  #  #  #  #   ",
};

TileEdge GetMatchingEdge(TileEdge e) {
	switch (e)
	{
	case TileEdge::Top:
		return TileEdge::Bottom;
	case TileEdge::Bottom:
		return TileEdge::Top;
	case TileEdge::Left:
		return TileEdge::Right;
	case TileEdge::Right:
		return TileEdge::Left;
	default:
		throw 1;
	}
}

void Day20::Run()
{
	auto inputs = InputParser::GetStrings("20.txt");

	Image i(inputs);

	i.Link();
	i.Sort();
	i.Stitch();

	auto m = i.master;

	for (int f = 0; f < 2; f++) {
		for (int r = 0; r < 4; r++) {
			if (m->HasSeaMonster()) {
				m->EraseSeaMonsters();
				int roughness = m->GetRoughness();

				m->Print();

				cout << roughness << endl;
				return;
			}
			m->Rotate();
		}
		m->Flip();
	}

	m->Print();
	cout << "could not find any sea monsters" << endl;
}

Image::Image(vector<string> inputs)
{
	static auto headerExp = regex("^Tile ([0-9]+):$");

	int currentID = -1;
	vector<string> currentTilePixels;
	for (auto i : inputs) {
		if (regex_match(i, headerExp)) {
			auto currentIDStr = regex_replace(i, headerExp, "$1");
			currentID = stoi(currentIDStr);
			continue;
		}

		bool newLine = i.length() == 0;
		if (newLine) {
			auto t = new Tile(currentID, currentTilePixels);
			tiles.push_back(t);
			currentTilePixels = vector<string>();
			continue;
		}

		currentTilePixels.push_back(i);
	}

	if (currentTilePixels.size() > 0) {
		auto t = new Tile(currentID, currentTilePixels);
		tiles.push_back(t);
	}
}

void Image::Link()
{
	auto root = tiles[0];
	TilePos p(0, 0);
	root->position = p;

	queue<Tile*> remaining;

	for (auto t : tiles) {
		if (t->id == root->id) {
			continue;
		}

		remaining.push(t);
	}

	while (remaining.size() > 0) {
		auto t = remaining.front();
		remaining.pop();

		bool success = root->Attach(t);
		if (!success) {
			remaining.push(t);
		}
	}
}

void Image::Sort()
{
	for (int y = GetMinY(); y < GetMinY() + GetDim(); y++) {
		vector<Tile*> row;
		for (int x = GetMinX(); x < GetMinX() + GetDim(); x++) {
			auto t = GetTileByPosition(x, y);
			row.push_back(t);
		}
		sortedTiles.push_back(row);
	}
}

void Image::Stitch()
{
	vector<string> pixels;

	int max = GetDim() * (GetTileDim() - 2);
	for (int y = 0; y < max; y++) {
		string row = "";
		for (int x = 0; x < max; x++) {
			row += GetStitchedPixel(x, y);
		}
		pixels.push_back(row);
	}

	master = new Tile(-1, pixels);
}

int Image::GetMinX() const
{
	int minX = INT_MAX;
	for (auto t : tiles) {
		minX = t->position.x < minX ? t->position.x : minX;
	}
	return minX;
}

int Image::GetMinY() const
{
	int minY = INT_MAX;
	for (auto t : tiles) {
		minY = t->position.y < minY ? t->position.y : minY;
	}
	return minY;
}

int Image::GetDim() const
{
	return sqrt(tiles.size());
}

int Image::GetTileDim() const
{
	return tiles[0]->GetDim();
}

Tile* Image::GetTileByPosition(int x, int y)
{
	for (auto t : tiles) {
		auto pos = t->position;
		if (pos.x == x && pos.y == y) {
			return t;
		}
	}
	throw 1;
}

// 0, 0 is the top left pixel without border
// data is sourced from sortedTiles
char Image::GetStitchedPixel(int x, int y) const
{
	// offset by 2 to account for border
	int dim = GetTileDim() - 2;
	int tileX = x / dim;
	int tileY = y / dim;

	auto t = sortedTiles[tileY][tileX];

	// offset by 1 for border
	int localX = 1 + x % dim;
	int localY = 1 + y % dim;
	return t->pixels[localY][localX];
}

string GetReverse(string in) {
	string out;
	for (int i = in.length() - 1; i >= 0; i--) {
		out += in[i];
	}

	return out;
}

std::vector<std::string> Tile::GetBorders() const
{
	vector<string> borders;

	for (auto e : allTileEdges) {
		auto border = GetBorder(e);
		borders.push_back(border);
	}

	return borders;
}

std::string Tile::GetBorder(TileEdge edge) const
{
	string border = "";
	int rightIndex = 0;
	switch (edge)
	{
	case TileEdge::Top:
		return pixels[0];
	case TileEdge::Bottom:
		return pixels[pixels.size() - 1];
	case TileEdge::Left:
		for (int i = 0; i < pixels.size(); i++) {
			border += pixels[i][0];
		}
		return border;
	case TileEdge::Right:
		rightIndex = pixels[0].length() - 1;
		for (int i = 0; i < pixels.size(); i++) {
			border += pixels[i][rightIndex];
		}
		return border;
	default:
		throw 1;
	}
}

int Tile::GetDim() const
{
	return pixels.size();
}

bool Tile::IsCorner() const
{
	return neighbors.size() == 2;
}

bool Tile::IsCompatible(TileEdge e, Tile* other) const
{
	auto borderToMatch = GetBorder(e);
	auto reverseMatch = GetReverse(borderToMatch);

	auto othersBorders = other->GetBorders();

	for (auto ob : othersBorders) {
		if (borderToMatch == ob) {
			return true;
		}

		if (reverseMatch == ob) {
			return true;
		}
	}

	return false;
}

// Rotates Tile 90 Degrees Clockwise
void Tile::Rotate()
{
	vector<string> newPixels;

	for (int c = 0; c < GetDim(); c++) {
		string newRow = "";
		for (int r = GetDim() - 1; r >= 0; r--) {
			newRow += pixels[r][c];
		}
		newPixels.push_back(newRow);
	}
	
	pixels = newPixels;
}

// Flips Tile horizontally
void Tile::Flip()
{
	vector<string> newPixels;

	for (int r = 0; r < GetDim(); r++) {
		string newRow = "";
		for (int c = GetDim() - 1; c >= 0; c--) {
			newRow += pixels[r][c];
		}
		newPixels.push_back(newRow);
	}

	pixels = newPixels;
}

bool Tile::Attach(Tile* t)
{
	for (auto e : allTileEdges) {
		// Attempt attachment to neighbor
		auto neighborItr = neighbors.find(e);
		if (neighborItr != neighbors.end()) {
			auto neighborTile = neighborItr->second;
			bool attachToNeighbor = neighborTile->Attach(t);
			if (attachToNeighbor) {
				return true;
			}
		}
		else if (SelfAttach(e, t)) {
			return true;
		}
	}

	return false;
}

bool Tile::HasSeaMonster() const
{
	for (int x = 0; x < GetDim(); x++) {
		for (int y = 0; y < GetDim(); y++) {
			if (IsSeaMonster(x, y)) {
				return true;
			}
		}
	}
	return false;
}

void Tile::EraseSeaMonsters()
{
	for (int x = 0; x < GetDim(); x++) {
		for (int y = 0; y < GetDim(); y++) {
			if (IsSeaMonster(x, y)) {
				EraseMonster(x, y);
			}
		}
	}
}

int Tile::GetRoughness() const
{
	int count = 0;

	for (int x = 0; x < GetDim(); x++) {
		for (int y = 0; y < GetDim(); y++) {
			if (pixels[y][x] == '#') {
				count++;
			}
		}
	}

	return count;
}

void Tile::Print() const
{
	for (auto row : pixels) {
		cout << row << endl;
	}
}

// Note: Lower = higher Y (similar to screen coords)
TilePos GetPositionAtEdge(const TilePos& p, TileEdge e) {
	switch (e)
	{
	case TileEdge::Top:
		return TilePos(p.x, p.y - 1);
	case TileEdge::Bottom:
		return TilePos(p.x, p.y + 1);
	case TileEdge::Left:
		return TilePos(p.x - 1, p.y);
	case TileEdge::Right:
		return TilePos(p.x + 1, p.y);
	default:
		throw 1;
	}
}

bool Tile::SelfAttach(TileEdge e, Tile* t)
{
	auto borderToMatch = GetBorder(e);

	// 2 ways to flip
	for (int f = 0; f < 2; f++) {
		t->Flip();
		// 4 rotations to check
		for (int r = 0; r < 4; r++) {
			t->Rotate();

			auto matchingEdge = GetMatchingEdge(e);

			auto otherBorder = t->GetBorder(matchingEdge);
			if (otherBorder == borderToMatch) {
				neighbors[e] = t;
				t->position = GetPositionAtEdge(position, e);
				return true;
			}
		}
	}

	return false;
}

void Tile::EraseMonster(int x, int y)
{
	for (int yOffset = 0; yOffset < seaMonster.size(); yOffset++) {
		for (int xOffset = 0; xOffset < seaMonster[0].size(); xOffset++) {
			if (seaMonster[yOffset][xOffset] == '#') {
				pixels[y + yOffset][x + xOffset] = 'O';
			}
		}
	}
}

bool Tile::IsSeaMonster(int x, int y) const
{
	for (int yOffset = 0; yOffset < seaMonster.size(); yOffset++) {
		for (int xOffset = 0; xOffset < seaMonster[0].size(); xOffset++) {
			if (
				seaMonster[yOffset][xOffset] == '#' &&
				GetChecked(x + xOffset, y + yOffset) != '#'
				) {
				return false;
			}
		}
	}

	return true;
}

char Tile::GetChecked(int x, int y) const
{
	if (x < 0 || x >= GetDim() || y < 0 || y >= GetDim()) {
		return ' ';
	}
	return pixels[y][x];
}
