#pragma once

#include "Base.h"

class CombatPlayer {
public:
	list<int> cards;
	CombatPlayer() {}

	int DrawCard();

	string GetDeck();
	int GetScore();

	list<int> PeekCards(int count);
};

class CombatGame {
public:
	static int idCounter;
	static map<string, int> results;

	int id;
	int round;
	int winOverride;
	vector<CombatPlayer*> players;
	set<string> history;

	CombatGame(vector<string> inputs);
	CombatGame(CombatPlayer* p0, int c0, CombatPlayer* p1, int c1);

	void Play();
	void PlayRound();
	bool IsOver();
	int GetWinner();

private:
	void Init();

	string GenerateHistoryHash() const;
};

class Day22
{
public:
	static void Run();
};

