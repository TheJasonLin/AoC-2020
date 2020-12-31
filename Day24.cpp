#include "Day24.h"

void Day24::Run()
{
	auto instructions = MakeInstructions();

	Lobby l;

	l.Apply(instructions);

	cout << l.GetBlackCount() << endl;

	for (int i = 1; i <= 100; i++) {
		l.Tick();
		cout << "Day " << i << ": " << l.GetBlackCount() << endl;
	}
}

std::vector<FlipInstruction*> Day24::MakeInstructions()
{
	auto inputs = InputParser::GetStrings("24.txt");

	vector<FlipInstruction*> instructions;
	for (auto i : inputs) {
		auto fi = new FlipInstruction(i);
		instructions.push_back(fi);
	}

	return instructions;
}

FlipInstruction::FlipInstruction(string input)
{
	static auto e = regex("^e(.*)$");
	static auto se = regex("^se(.*)$");
	static auto sw = regex("^sw(.*)$");
	static auto w = regex("^w(.*)$");
	static auto nw = regex("^nw(.*)$");
	static auto ne = regex("^ne(.*)$");

	source = input;

	string c = input;
	while (c.length() > 0) {
		if (regex_match(c, e)) {
			path.push_back(HexDirection::East);
			c = regex_replace(c, e, "$1");
		}
		else if (regex_match(c, se)) {
			path.push_back(HexDirection::SouthEast);
			c = regex_replace(c, se, "$1");
		}
		else if (regex_match(c, sw)) {
			path.push_back(HexDirection::SouthWest);
			c = regex_replace(c, sw, "$1");
		}
		else if (regex_match(c, w)) {
			path.push_back(HexDirection::West);
			c = regex_replace(c, w, "$1");
		}
		else if (regex_match(c, nw)) {
			path.push_back(HexDirection::NorthWest);
			c = regex_replace(c, nw, "$1");
		}
		else if (regex_match(c, ne)) {
			path.push_back(HexDirection::NorthEast);
			c = regex_replace(c, ne, "$1");
		}
		else {
			throw 1;
		}
	}
}

CubePos FlipInstruction::GetEndOfPath()
{
	CubePos cur(0, 0, 0);

	// reference: https://www.redblobgames.com/grids/hexagons/
	for (auto dir : path) {
		switch (dir)
		{
		case HexDirection::East:
			cur.x += 1;
			cur.y -= 1;
			break;
		case HexDirection::SouthEast:
			cur.z += 1;
			cur.y -= 1;
			break;
		case HexDirection::SouthWest:
			cur.z += 1;
			cur.x -= 1;
			break;
		case HexDirection::West:
			cur.y += 1;
			cur.x -= 1;
			break;
		case HexDirection::NorthWest:
			cur.y += 1;
			cur.z -= 1;
			break;
		case HexDirection::NorthEast:
			cur.x += 1;
			cur.z -= 1;
			break;
		default:
			throw 1;
		}
	}

	return cur;
}

void LobbyTile::Flip()
{
	black = !black;
}

Lobby::Lobby()
{
}

void Lobby::Apply(vector<FlipInstruction*> instructions)
{
	for (auto i : instructions) {
		auto targetPos = i->GetEndOfPath();
		auto t = GetTile(targetPos);
		t->Flip();
	}
}

int Lobby::GetBlackCount()
{
	int count = 0;
	for (auto entry : tiles) {
		auto t = entry.second;
		if (t->black) {
			count++;
		}
	}

	return count;
}

void Lobby::AddTile(LobbyTile* tile)
{
	auto hash = tile->pos.GetHash();
	tiles[hash] = tile;
}

LobbyTile* Lobby::GetTile(const CubePos& pos)
{
	auto hash = pos.GetHash();
	auto tilesItr = tiles.find(hash);
	if (tilesItr != tiles.end()) {
		return tilesItr->second;
	}

	auto t = new LobbyTile(pos);
	AddTile(t);
	return t;
}

void Lobby::Tick()
{
	auto poi = GetPOI();

	auto tempLobby = new Lobby();

	for (auto p : poi) {
		auto blackCount = GetAdjacentBlackCount(p);
		if (IsBlack(p)) {
			if (blackCount == 0 || blackCount > 2) {
				// flip to white = do nothing
			}
			else {
				auto t = tempLobby->GetTile(p);
				t->Flip();
				t->black = true;
			}
			continue;
		}

		if (blackCount == 2) {
			auto t = tempLobby->GetTile(p);
			t->Flip();
		}
	}

	// transfer tiles simultaneously and only keep black ones
	tiles = tempLobby->tiles;
}

std::vector<CubePos> Lobby::GetPOI() const
{
	vector<CubePos> out;
	set<string> hashset;
	for (auto entry : tiles) {
		auto t = entry.second;
		// white is not in itself interesting
		if (!t->black) {
			continue;
		}

		// itself is interesting
		auto hash = t->pos.GetHash();
		if (hashset.find(hash) == hashset.end()) {
			out.push_back(t->pos);
			hashset.insert(hash);
		}
		// get every tile adjacent to black tile
		auto adjacentPos = t->pos.GetAdjacent();
		for (auto p : adjacentPos) {
			auto hash = p.GetHash();
			if (hashset.find(hash) == hashset.end()) {
				out.push_back(p);
				hashset.insert(hash);
			}
		}
	}
	return out;
}

int Lobby::GetAdjacentBlackCount(const CubePos& p) const
{
	int count = 0;
	auto adjacentPos = p.GetAdjacent();
	for (auto p : adjacentPos) {
		if (IsBlack(p)) {
			count++;
		}
	}

	return count;
}

bool Lobby::IsBlack(const CubePos& pos) const
{
	auto hash = pos.GetHash();
	auto tileItr = tiles.find(hash);

	if (tileItr == tiles.end()) {
		return false;
	}

	return tileItr->second->black;
}

std::string CubePos::GetHash() const
{
	stringstream sout;

	sout << x << "," << y << "," << z;

	return sout.str();
}

std::vector<CubePos> CubePos::GetAdjacent() const
{
	vector<CubePos> out = {
		CubePos(this->x + 1, this->y - 1, this->z),
		CubePos(this->x + 1, this->y, this->z - 1),
		CubePos(this->x - 1, this->y + 1, this->z),
		CubePos(this->x - 1, this->y, this->z + 1),
		CubePos(this->x, this->y + 1, this->z - 1),
		CubePos(this->x, this->y - 1, this->z + 1),
	};

	return out;
}
