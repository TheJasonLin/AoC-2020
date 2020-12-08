#pragma once

#include "InputParser.h"
#include <iostream>

using namespace std;

inline bool check(vector<int> values, int target) {
	int sum = 0;

	for (auto value : values) {
		sum += value;
	}
	return sum == target;
}

inline void run() {
	auto input = InputParser::GetInts("day1.txt");

	for (int i = 0; i < input.size(); i++) {
		for (int j = 0; j < input.size(); j++) {
			for (int k = 0; k < input.size(); k++) {
				if (i == j || j == k || i == k) {
					continue;
				}

				if (check({ input[i], input[j], input[k] }, 2020)) {
					cout << input[i] << endl;
					cout << input[j] << endl;
					cout << input[k] << endl;
					cout << input[i] * input[j] * input[k] << endl;
					return;
				}
			}
		}
	}
}

