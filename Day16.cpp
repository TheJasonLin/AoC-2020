#include "Day16.h"

void Day16::Run1()
{
	auto inputs = InputParser::GetStrings("16.txt");

	TrainStation s(inputs);

	int sum = 0;
	for (auto t : s.nearbyTickets) {
		int badValue;
		if (!t->IsValid(s.rules, badValue)) {
			sum += badValue;
		}
	}

	cout << sum << endl;
}

void Day16::Run()
{
	auto inputs = InputParser::GetStrings("16.txt");

	TrainStation s(inputs);

	auto validTickets = s.GetValidTickets();

	auto fieldCount = s.myTicket->values.size();
	// [field][value]
	vector<set<int>> fieldValues;
	// initialize with N empty sets, where N = number of fields / values
	for (int i = 0; i < fieldCount; i++) {
		fieldValues.push_back({});
	}
	// populate possible values
	for (auto t : validTickets) {
		for (int i = 0; i < t->values.size(); i++) {
			fieldValues[i].insert(t->values[i]);
		}
	}
	// Create independent mapping of valid rules for each field
	vector<set<Rule*>> fieldRules;
	for (int i = 0; i < fieldCount; i++) {
		set<Rule*> possibleRules = s.rules;
		auto valueSet = fieldValues[i];

		for (auto v : valueSet) {
			set<Rule*> newPossibleRules;
			for (auto r : possibleRules) {
				if (r->IsValueAllowed(v)) {
					newPossibleRules.insert(r);
				}
			}
			possibleRules = newPossibleRules;
		}
		fieldRules.push_back(possibleRules);
	}

	cout << " ----- Initial ------" << endl;
	PrintFieldRules(fieldRules, fieldCount);

	map<int, Rule*> solution;
	while (solution.size() < fieldCount) {
		Rule* lockedRule;
		for (int i = 0; i < fieldCount; i++) {
			if (fieldRules[i].size() == 1) {
				lockedRule = *fieldRules[i].begin();
				solution[i] = lockedRule;
				break;
			}
		}
		// remove that rule from other sets
		for (auto& r : fieldRules) {
			r.erase(lockedRule);
		}
	}

	cout << "------ Solution -----" << endl;
	// Label My Ticket
	for (int i = 0; i < fieldCount; i++) {
		auto field = solution[i]->field;
		auto value = s.myTicket->values[i];
		cout << field << ": " << value << endl;
	}
}

void Day16::PrintFieldRules(vector<set<Rule*>> fieldRules, int fieldCount)
{
	// Print Result
	for (int i = 0; i < fieldCount; i++) {
		cout << i << ": ";

		for (auto r : fieldRules[i]) {
			cout << "[" << r->field << "]";
		}
		cout << endl;
	}
}

TrainStation::TrainStation(vector<string> inputs) {
	static auto ruleReg = regex("^([a-z ]+): ([0-9]+)-([0-9]+) or ([0-9]+)-([0-9]+)$");
	static auto ticketReg = regex("^([0-9]+)(,[0-9]+)*$");
	static auto myTicketReg = regex("^your ticket:$");
	static auto nearbyTicketReg = regex("^nearby tickets:$");
	// phase: 0=Rules, 1=YourTicket, 2 = Nearby Tickets
	auto phase = 0;
	for (auto i : inputs) {
		// ignore empty lines
		if (i.length() == 0) {
			continue;
		}

		if (phase == 0) {
			if (regex_match(i, myTicketReg)) {
				phase = 1;
				continue;
			}

			auto field = regex_replace(i, ruleReg, "$1");
			auto min1 = stoi(regex_replace(i, ruleReg, "$2"));
			auto max1 = stoi(regex_replace(i, ruleReg, "$3"));
			auto min2 = stoi(regex_replace(i, ruleReg, "$4"));
			auto max2 = stoi(regex_replace(i, ruleReg, "$5"));
			auto r = new Rule(i, field, min1, max1, min2, max2);
			rules.insert(r);
		}
		else if (phase == 1) {
			myTicket = new Ticket(i);
			phase = 2;
			continue;
		}
		else {
			// ignore header
			if (regex_match(i, nearbyTicketReg)) {
				continue;
			}

			auto t = new Ticket(i);
			nearbyTickets.push_back(t);
		}
	}
}

vector<Ticket*> TrainStation::GetValidTickets()
{
	vector<Ticket*> out = { myTicket };

	for (auto t : nearbyTickets) {
		int unused;
		if (t->IsValid(rules, unused)) {
			out.push_back(t);
		}
	}

	return out;
}

Rule::Rule(string source, string field, int min1, int max1, int min2, int max2) :
	source(source),
	field(field)
{
	ranges = {
		{min1, max1},
		{min2, max2},
	};
}

bool Rule::IsValueAllowed(int value) const
{
	for (auto range : ranges) {
		if (value >= range.first && value <= range.second) {
			return true;
		}
	}
	return false;
}

Ticket::Ticket(string input) :
	source(input)
{
	static auto xXS = regex("^([0-9]+),(.*)$");

	auto current = input;
	while (regex_match(current, xXS)) {
		auto valueStr = regex_replace(current, xXS, "$1");
		auto value = stoi(valueStr);

		values.push_back(value);

		current = regex_replace(current, xXS, "$2");
	}

	auto value = stoi(current);
	values.push_back(value);
}

bool Ticket::IsValid(set<Rule*> rules, int& outBadValue)
{
	for (auto v : values) {
		auto foundRule = false;
		for (auto rule : rules) {
			if (rule->IsValueAllowed(v)) {
				foundRule = true;
				break;
			}
		}

		if (!foundRule) {
			outBadValue = v;
			return false;
		}
	}
	return true;
}
