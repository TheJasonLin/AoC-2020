#include "Day19.h"

const auto literalRuleExp = regex("^\"(.)\"$");
const auto orRuleExp = regex("^(.*) \\| (.*)$");

void Day19::Run()
{
	auto inputs = InputParser::GetStrings("19.txt");

	RuleSet s(inputs);

	cout << s.GetValidCount() << endl;
}

LiteralRule::LiteralRule(string input)
{
	auto charStr = regex_replace(input, literalRuleExp, "$1");
	literal = charStr[0];
}

string LiteralRule::GetRegex(const RuleSet* s) const
{
	return string(1, literal);
}

CompositeRule::CompositeRule(string input)
{
	static auto xxs = regex("^([0-9]+) (.*)$");
	static auto x = regex("^([0-9]+)$");

	auto current = input;
	while (regex_match(current, xxs)) {
		auto numberStr = regex_replace(current, xxs, "$1");
		auto number = stoi(numberStr);
		numbers.push_back(number);

		current = regex_replace(current, xxs, "$2");
	}

	auto numberStr = regex_replace(current, x, "$1");
	auto number = stoi(numberStr);
	numbers.push_back(number);
}

string CompositeRule::GetRegex(const RuleSet* s) const
{
	string e = "";
	for (auto n : numbers) {
		auto rItr = s->rules.find(n);
		if (rItr == s->rules.end()) {
			throw 1;
		}
		auto r = rItr->second;
		auto componentExp = r->GetRegex(s);
		e += componentExp;
	}
	
	return e;
}

OrRule::OrRule(string input)
{
	auto leftRuleInput = regex_replace(input, orRuleExp, "$1");
	auto rightRuleInput = regex_replace(input, orRuleExp, "$2");

	a = new CompositeRule(leftRuleInput);
	b = new CompositeRule(rightRuleInput);
}

string OrRule::GetRegex(const RuleSet* s) const
{
	return "(" + a->GetRegex(s) + "|" + b->GetRegex(s) + ")";
}

RuleSet::RuleSet(vector<string> inputs)
{
	static auto ruleExp = regex("^([0-9]+): (.*)$");

	for (auto i : inputs) {
		// Rule Definition Case
		if (regex_match(i, ruleExp)) {
			auto numberStr = regex_replace(i, ruleExp, "$1");
			auto number = stoi(numberStr);
			auto value = regex_replace(i, ruleExp, "$2");

			auto r = MakeRule(value);

			rules[number] = r;
			
			continue;
		}

		// expect 1 empty line
		if (i.length() == 0) {
			continue;
		}

		// Message Case
		messages.push_back(i);
	}
}

int RuleSet::GetValidCount() const
{
	int count = 0;
	auto masterRule = rules.find(0)->second;
	if (!masterRule) {
		throw 1;
	}

	for (auto m : messages) {
		if (masterRule->Matches(m, this)) {
			count++;
		}
	}
	
	return count;
}

Rule* RuleSet::MakeRule(string input)
{
	if (regex_match(input, literalRuleExp)) {
		return new LiteralRule(input);
	}
	else if (regex_match(input, orRuleExp)) {
		return new OrRule(input);
	}
	else {
		return new CompositeRule(input);
	}
}

bool Rule::Matches(string input, const RuleSet* s)
{
	string eStr = "^" + GetRegex(s) + "$";
	auto e = regex(eStr);

	return regex_match(input, e);
}
