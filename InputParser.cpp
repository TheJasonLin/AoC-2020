#include "InputParser.h"
#include <iostream>
#include <fstream>

vector<string> InputParser::GetStrings(string fileName)
{
	vector<string> out;
	string line;
	ifstream file("inputs/" + fileName);
	if (file.is_open()) {
		while (getline(file, line)) {
			out.push_back(line);
		}
		file.close();
	}
	else {
		cout << "unable to open file: " + fileName;
	}

	return out;
}

vector<int> InputParser::GetInts(string fileName)
{
	vector<int> out;

	auto strings = GetStrings(fileName);

	for (auto str : strings) {
		int i = stoi(str);
		out.push_back(i);
	}

	return out;
}

std::vector<long long> InputParser::GetLongLongs(string fileName)
{
	vector<long long> out;

	auto strings = GetStrings(fileName);

	for (auto str : strings) {
		int i = stoll(str);
		out.push_back(i);
	}

	return out;
}
