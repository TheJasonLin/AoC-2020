#include "Day22.h"

void Day22::Run()
{
	auto inputs = InputParser::GetStrings("22.txt");

	CombatGame g(inputs);

	g.Play();

	cout << "Player 1 Score: " << g.players[0]->GetScore() << endl;
	cout << "Player 2 Score: " << g.players[1]->GetScore() << endl;
}

int CombatGame::idCounter = 0;

std::map<std::string, int> CombatGame::results = {};

CombatGame::CombatGame(vector<string> inputs)
{
	Init();

	static auto numberExp = regex("^[0-9]+$");
	players.push_back(new CombatPlayer());
	players.push_back(new CombatPlayer());

	int currentPlayer = 0;
	for (auto i : inputs) {
		if (i == "Player 2:") {
			currentPlayer = 1;
			continue;
		}

		if (regex_match(i, numberExp)) {
			auto num = stoi(i);
			players[currentPlayer]->cards.push_back(num);
		}
	}
}

CombatGame::CombatGame(CombatPlayer* p0, int c0, CombatPlayer* p1, int c1)
{
	Init();

	CombatPlayer* new0 = new CombatPlayer();
	new0->cards = p0->PeekCards(c0);
	players.push_back(new0);

	CombatPlayer* new1 = new CombatPlayer();
	new1->cards = p1->PeekCards(c1);
	players.push_back(new1);
}

void CombatGame::Play()
{
	auto hash = GenerateHistoryHash();

	if (results.find(hash) != results.end()) {
		winOverride = results.find(hash)->second;
	}

	while (!IsOver()) {
		PlayRound();
	}

	results[hash] = GetWinner();
}

void CombatGame::PlayRound()
{
	cout << "-- Round " << round++ << "(Game " << id << ")" << " --" << endl;
	auto hash = GenerateHistoryHash();
	if (history.find(hash) != history.end()) {
		winOverride = 0;
		cout << "Recursion Win" << endl;
		return;
	}
	history.insert(hash);

	auto c0 = players[0]->DrawCard();
	auto c1 = players[1]->DrawCard();

	int winnerIndex = -1;

	// Recursive Game Case
	if (players[0]->cards.size() >= c0 && players[1]->cards.size() >= c1) {
		CombatGame sub(players[0], c0, players[1], c1);
		sub.Play();
		winnerIndex = sub.GetWinner();
	}
	// Standard Game Case
	else {
		if (c0 > c1) {
			winnerIndex = 0;
		}
		else {
			winnerIndex = 1;
		}
	}

	// Add cards to winner deck
	if (winnerIndex == 0) {
		players[0]->cards.push_back(c0);
		players[0]->cards.push_back(c1);
	}
	else {
		players[1]->cards.push_back(c1);
		players[1]->cards.push_back(c0);
	}

	// Print State
	//cout << "Player 1: " << players[0]->GetDeck() << endl;
	//cout << "Player 2: " << players[1]->GetDeck() << endl;
}

bool CombatGame::IsOver()
{
	if (winOverride > -1) {
		return true;
	}

	for (auto p : players) {
		if (p->cards.size() == 0) {
			return true;
		}
	}
	return false;
}

int CombatGame::GetWinner()
{
	if (winOverride > -1) {
		return winOverride;
	}

	if (players[0]->cards.size() > 0) {
		return 0;
	}
	else {
		return 1;
	}
}

void CombatGame::Init()
{
	id = idCounter++;
	round = 1;
	winOverride = -1;
}

string CombatGame::GenerateHistoryHash() const
{
	stringstream sout;

	sout << players[0]->GetDeck() << " | " << players[1]->GetDeck();

	return sout.str();
}

int CombatPlayer::DrawCard()
{
	auto card = cards.front();
	cards.pop_front();
	return card;
}

std::string CombatPlayer::GetDeck()
{
	stringstream sout;
	for (auto c : cards) {
		sout << c << " ";
	}
	return sout.str();
}

int CombatPlayer::GetScore()
{
	int sum = 0;

	for (int weight = cards.size(); cards.size() > 0; weight--) {
		auto card = DrawCard();
		sum += card * weight;
	}

	return sum;
}

std::list<int> CombatPlayer::PeekCards(int count)
{
	list<int> subset;
	for (auto c : cards) {
		if (subset.size() == count) {
			break;
		}
		subset.push_back(c);
	}
	return subset;
}
