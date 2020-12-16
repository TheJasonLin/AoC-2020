#pragma once

#include "Base.h"

class Rule {
public:
	vector<pair<int, int>> ranges;
	string field;
	string source;
	Rule(string source, string field, int min1, int max1, int min2, int max2);

	bool IsValueAllowed(int value) const;
};

class Ticket {
public:
	string source;
	vector<int> values;

	Ticket(string input);

	bool IsValid(set<Rule*> rules, int& outBadValue);
};

class TrainStation {
public:
	set<Rule*> rules;
	Ticket* myTicket;
	vector<Ticket*> nearbyTickets;

	TrainStation(vector<string> inputs);
	vector<Ticket*> GetValidTickets();
};

class Day16
{
public:
	static void Run1();
	static void Run();

	static void PrintFieldRules(vector<set<Rule*>> fieldRules, int fieldCount);
};

