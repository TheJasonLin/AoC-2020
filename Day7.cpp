#include "Day7.h"


void Bag::AddRelationship(Relationship* r)
{
	if (r->container == this) {
		contents.push_back(r);
	}
	else if (r->content == this) {
		containers.push_back(r);
	}
}

std::set<Bag*> Bag::GetSuperContainers() const
{
	set<Bag*> out;

	for (auto r : containers) {
		auto container = r->container;
		out.insert(container);
		auto containerSet = r->container->GetSuperContainers();
		out.insert(containerSet.begin(), containerSet.end());
	}
	 
	return out;
}

int Bag::GetContentCount() const
{
	int count = 0;

	for (auto r : contents) {
		auto content = r->content;
		
		count += r->count + r->count * content->GetContentCount();
	}
	return count;
}

void Airport::AddEntry(string input)
{
	auto colorAndRules = regex("^([a-z ]+) bags contain (.*)$");

	auto color = regex_replace(input, colorAndRules, string("$1"));
	auto rules = regex_replace(input, colorAndRules, string("$2"));

	auto bag = GetBag(color);
	AddRules(bag, rules);
}

Bag* Airport::GetBag(string color)
{
	auto bagIt = bags.find(color);
	Bag* bag = bagIt != bags.end() ? bagIt->second : new Bag(color);
	bags[color] = bag;
	return bag;
}

void Airport::AddRules(Bag* container, string rules)
{
	static auto none = regex("^no other bags\\.$");
	static auto parseFirst = regex("^([0-9]+) ([a-z ]+) bags?(\\.|, )(.*)$");

	auto current = rules;

	while (true) {
		if (regex_match(current, none)) {
			return;
		}
		if (current.length() < 1) {
			return;
		}

		auto countStr = regex_replace(current, parseFirst, string("$1"));
		auto count = stoi(countStr);
		auto color = regex_replace(current, parseFirst, string("$2"));
		
		auto content = GetBag(color);

		auto r = new Relationship(container, content, count);
		container->AddRelationship(r);
		content->AddRelationship(r);
		
		current = regex_replace(current, parseFirst, string("$4"));
	}
}

void Day7::Run()
{
	auto a = GetAirport();

	auto root = a->bags["shiny gold"];

	auto superContainers = root->GetSuperContainers();

	cout << "Container Count: " << superContainers.size() << endl;

	cout << "Content Count: " << root->GetContentCount() << endl;
}

Airport* Day7::GetAirport()
{
	auto strings = InputParser::GetStrings("7.txt");

	auto a = new Airport();
	for (auto s : strings) {
		a->AddEntry(s);
	}

	return a;
}
