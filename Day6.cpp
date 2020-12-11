#include "Day6.h"

Person::Person(string input):
	source(input)
{
	for (auto c : input) {
		questions.push_back(c);
	}
}

int Group::GetUnique() const
{
	set<char> questions;

	for (auto p : People) {
		for (auto q : p.questions) {
			questions.insert(q);
		}
	}

	return questions.size();
}

int Group::GetCommon() const
{
	set<char> common;
	
	for (auto q : People[0].questions) {
		common.insert(q);
	}

	for (auto p : People) {
		set<char> pQuestions;
		for (auto q : p.questions) {
			pQuestions.insert(q);
		}

		for (auto it = common.begin(); it != common.end();) {
			if (pQuestions.find(*it) == pQuestions.end()) {
				common.erase(it++);
			}
			else {
				++it;
			}
		}
	}

	return common.size();
}

void Day6::Run()
{
	auto groups = GetGroups();

	int sum = 0;

	for (auto g : groups) {
		sum += g.GetUnique();
	}

	cout << sum << endl;
}

void Day6::Run2()
{
	auto groups = GetGroups();

	int sum = 0;

	for (auto g : groups) {
		sum += g.GetCommon();
	}

	cout << sum << endl;
}

std::vector<Group> Day6::GetGroups()
{
	auto strings = InputParser::GetStrings("6.txt");

	vector<Group> groups;

	Group g;
	for (auto s : strings) {
		if (s == "") {
			groups.push_back(g);
			g = Group();
			continue;
		}
		Person p(s);
		g.People.push_back(p);
	}
	// last group has no trailing empty line
	groups.push_back(g);

	return groups;
}
