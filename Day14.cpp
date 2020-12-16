#include "Day14.h"

void Day14::Run()
{
	auto inputs = InputParser::GetStrings("14.txt");

	Computer c;

	static auto maskReg = regex("^mask = ([01X]+)$");
	static auto writeMask = regex("^mem\\[([0-9]+)\\] = ([0-9]+)$");
	string currentMask;
	for (auto i : inputs) {
		if (regex_match(i, maskReg)) {
			currentMask = regex_replace(i, maskReg, "$1");
			continue;
		}

		auto addressStr = regex_replace(i, writeMask, "$1");
		auto valueStr = regex_replace(i, writeMask, "$2");

		auto address = stoi(addressStr);
		auto value = stoull(valueStr);

		// part 2 does not use masked value at all
		auto maskedValue = GetMaskedValue(currentMask, value);
		if (maskedValue < 0) {
			throw 1;
		}

		auto maskedAddresses = GetMaskedAddresses(currentMask, address);
		for (auto a : maskedAddresses) {
			c.memory[a] = value;
		}
	}
	
	unsigned long long sum = 0;
	for (auto entry : c.memory) {
		sum += entry.second;
	}

	cout << sum << endl;
}

unsigned long long Day14::GetMaskedValue(string mask, unsigned long long value)
{
	// decimal value
	// OR with mask where everything is zero except the 1's in original mask
	// AND with mask where everything is 1 except the 0's in original mask
	unsigned long long orMask = 0;
	unsigned long long andMask = 0;
	for (auto bit : mask) {
		if (bit == '1') {
			orMask++;
		}

		if (bit != '0') {
			andMask++;
		}

		orMask = orMask << 1;
		andMask = andMask << 1;
	}

	// Undo last shift, which was unnecessary
	orMask = orMask >> 1;
	andMask = andMask >> 1;

	unsigned long long afterOr = value | orMask;
	unsigned long long afterAnd = afterOr & andMask;

	return afterAnd;
}

vector<unsigned long long> Day14::GetMaskedAddresses(string mask, unsigned long long address)
{
	// Apply force 1 Mask
	unsigned long long oneMask = 0;
	for (auto bit : mask) {
		if (bit == '1') {
			oneMask++;
		}

		oneMask = oneMask << 1;
	}
	oneMask = oneMask >> 1;

	unsigned long long afterOneMask = address | oneMask;

	// Create Masks to force X bits as both 0 and 1
	vector<unsigned long long> orMasks;
	vector<unsigned long long> andMasks;
	for (int i = 0; i < mask.length(); i++) {
		auto bit = mask[mask.length() - 1 - i];
	
		if (bit != 'X') {
			continue;
		}

		unsigned long long value = pow(2, i);

		orMasks.push_back(value);
		andMasks.push_back(~value);
	}

	// Apply every mask to every address
	vector<unsigned long long> addresses = { afterOneMask };
	for (int i = 0; i < orMasks.size(); i++) {
		auto orMask = orMasks[i];
		auto andMask = andMasks[i];

		vector<unsigned long long> newAddresses;
		for (auto a : addresses) {
			auto orValue = a | orMask;
			auto andValue = a & andMask;
			newAddresses.push_back(orValue);
			newAddresses.push_back(andValue);
		}
		addresses = newAddresses;
	}

	return addresses;
}
