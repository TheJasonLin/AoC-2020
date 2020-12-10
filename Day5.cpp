#include "Day5.h"

pair<int, int> SplitRange(pair<int, int> initial, char direction) {
	if (initial.first >= initial.second) {
		return initial;
	}

	int mid = (initial.first + initial.second) / 2;

	switch (direction)
	{
	case 'F':
		// fallthrough
	case 'L':
		return { initial.first, mid };
	case 'B':
		// fallthrough
	case 'R':
		return { mid + 1, initial.second };
	default:
		throw 1;
	}
}

Seat::Seat(string input)
{
	auto e = regex("^([FB]+)([LR]+)$");

	auto rowCode = regex_replace(input, e, string("$1"));
	auto colCode = regex_replace(input, e, string("$2"));

	pair<int, int> rowRange = { 0, 127 };
	for (auto c : rowCode) {
		rowRange = SplitRange(rowRange, c);
	}

	pair<int, int> colRange = { 0, 7 };
	for (auto c : colCode) {
		colRange = SplitRange(colRange, c);
	}

	row = rowRange.first;
	col = colRange.second;
	id = row * 8 + col;
}


void Day5::Run()
{
	auto input = InputParser::GetStrings("5.txt");

	vector<Seat> seats;

	int max = 0;
	for (auto i : input) {
		auto s = Seat(i);
		seats.push_back(s);
		if (s.id > max) {
			max = s.id;
		}
	}

	auto f = [](Seat i, Seat j) { return i.id < j.id; };
	sort(seats.begin(), seats.end(), f);

	cout << "Last Seat: " << seats[seats.size() - 1].id << endl;

	int lastID = seats[0].id;
	for (int i = 1; i < seats.size(); i++) {
		if (seats[i].id - lastID > 1) {
			cout << "Your Seat: " << lastID + 1 << endl;
			return;
		}
		lastID = seats[i].id;
	}
}
