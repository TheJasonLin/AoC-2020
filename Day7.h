#pragma once

#include "Base.h"

class Bag;

class Relationship
{
public:
	Bag* container;
	Bag* content;
	int count;

	Relationship(Bag* container, Bag* content, int count) :
		container(container),
		content(content),
		count(count)
	{}
};

class Bag
{
public:
	string color;
	vector<Relationship*> containers;
	vector<Relationship*> contents;

	Bag(string color) :
		color(color)
	{}

	void AddRelationship(Relationship* r);
	set<Bag*> GetSuperContainers() const;
	int GetContentCount() const;
};

class Airport
{
public:
	map<string, Bag*> bags;

	void AddEntry(string input);

private:
	Bag* GetBag(string color);
	void AddRules(Bag* container, string rules);
};

class Day7
{
public:
	static void Run();

private:
	static Airport* GetAirport();
};

