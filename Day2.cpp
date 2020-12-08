#include "Day2.h"
#include "InputParser.h"
#include <iostream>
#include <string>
#include <regex>

using namespace std;

void Day2::Run1()
{
	auto inputs = GetInputs();
	
	int count = 0;

	for (auto i : inputs) {
		int charOccurence = 0;

		for (auto c : i.password) {
			if (c == i.rule.character) {
				charOccurence++;
			}
		}

		if (charOccurence >= i.rule.min && charOccurence <= i.rule.max) {
			count++;
		}
	}

	cout << count << endl;
}

void Day2::Run2()
{
	auto inputs = GetInputs();

	int count = 0;

	for (auto i : inputs) {
		char first = i.password[i.rule.min - 1];
		char second = i.password[i.rule.max - 1];

		bool firstMatches = first == i.rule.character;
		bool secondMatches = second == i.rule.character;

		if (firstMatches ^ secondMatches) {
			count++;
			cout << i.source << endl;
		}
	}

	cout << count << endl;
}

vector<Input> Day2::GetInputs()
{
	vector<Input> out;
	static auto e = regex("([0-9]+)-([0-9]+) ([a-z]): ([a-z]+)");

	auto strings = InputParser::GetStrings("day2.txt");

	for (auto s : strings) {
		string min = regex_replace(s, e, string("$1"));
		string max = regex_replace(s, e, string("$2"));
		string character = regex_replace(s, e, string("$3"));
		string password = regex_replace(s, e, string("$4"));

		auto r = Rule(stoi(min), stoi(max), character[0]);
		auto i = Input(r, password, s);
		out.push_back(i);
	}
	return out;
}
