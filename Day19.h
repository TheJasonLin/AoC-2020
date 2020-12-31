#pragma once

#include "Base.h"

class RuleSet;

class Rule {
public:
	bool Matches(string input, const RuleSet* s);
	virtual string GetRegex(const RuleSet* s) const = 0;
};

class LiteralRule : public Rule {
public:
	char literal;

	LiteralRule(string input);

	string GetRegex(const RuleSet* s) const override;
};

class CompositeRule : public Rule {
public:
	vector<int> numbers;

	CompositeRule(string input);

	string GetRegex(const RuleSet* s) const override;

};

class OrRule : public Rule {
public:
	CompositeRule* a;
	CompositeRule* b;

	OrRule(string input);

	string GetRegex(const RuleSet* s) const override;
};

class RuleSet {
public:
	map<int, Rule*> rules;
	vector<string> messages;

	RuleSet(vector<string> inputs);

	int GetValidCount() const;
private:
	static Rule* MakeRule(string input);
};

class Day19
{
public:
	static void Run();
};

