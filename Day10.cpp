#include "Day10.h"

void Adapter::InitChildren(map<int, Adapter*> adapters)
{
	for (auto entry : adapters) {
		auto childJolts = entry.first;
		if (childJolts < jolts && jolts - childJolts <= 3) {
			children.push_back(entry.second);
		}
	}
}

long long Adapter::GetArrangements()
{
	if (cachedArragements != -1) {
		return cachedArragements;
	}

	if (children.size() == 0) {
		return 1;
	}

	long long sum = 0;

	for (auto c : children) {
		sum += c->GetArrangements();
	}

	cachedArragements = sum;
	return sum;
}

Bag::Bag(vector<int> numbers)
{
	// Create Variable Adapters
	int maxValue = numbers[0];
	for (auto n : numbers) {
		maxValue = n > maxValue ? n : maxValue;

		auto a = new Adapter(n);
		adapters.insert({ n, a });
	}

	// Create Device
	auto deviceJolts = maxValue + 3;
	myDevice = new Adapter(deviceJolts);
	adapters.insert({ deviceJolts, myDevice });

	// Create Outlet
	auto outlet = new Adapter(0);
	adapters.insert({ 0, outlet });

	// Build Mapping
	for (auto entry : adapters) {
		entry.second->InitChildren(adapters);
	}
}

Bag::~Bag()
{
	for (auto entry : adapters) {
		delete(entry.second);
	}

	delete(myDevice);
}

long long Bag::GetArrangements() const
{
	return myDevice->GetArrangements();
}

void Day10::Run()
{
	auto numbers = InputParser::GetInts("10.txt");

	Bag b(numbers);

	cout << b.GetArrangements() << endl;
}
