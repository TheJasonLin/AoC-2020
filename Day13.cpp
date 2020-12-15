#include "Day13.h"

void Day13::Run()
{
	auto strings = InputParser::GetStrings("13.txt");

	Problem p(strings);
	auto b = p.GetEarliestBus();
	auto t = b.GetFirstDepartureAfter(p.earliestTime);
	auto r = b.id * (t - p.earliestTime);
	cout << b.id << " * (" << t << " - " << p.earliestTime << ")" << " = " << r << endl;
}

void Day13::Run2()
{
	// Use Wolfram Alpha
	// https://www.wolframalpha.com/input/?i=t%2B0%3D29*a%2C+t%2B19%3D41*b%2C+t%2B29%3D661*c%2C+t%2B42%3D13*d%2C+t%2B43%3D17*e%2C+t%2B52%3D23*f%2C+t%2B60%3D521*g%2C+t%2B66%3D37*h%2C+t%2B79%3D19*i
}

Problem::Problem(vector<string> input)
{
	auto earliestStr = input[0];
	earliestTime = stoi(earliestStr);

	static auto e = regex("^([0-9]+|x)(.*)$");
	auto current = input[1];
	
	while (current.length() > 0) {
		auto busIDStr = regex_replace(current, e, "$1");
		current = regex_replace(current, e, "$2");
		if (current[0] == ',') {
			current = current.substr(1);
		}

		if (busIDStr == "x") {
			continue;
		}

		auto busID = stoi(busIDStr);
		Bus b(busID);
		busses.push_back(b);
	}
}

Bus Problem::GetEarliestBus() const
{
	Bus greedyBus = busses[0];
	for (auto b : busses) {
		auto bTime = b.GetFirstDepartureAfter(earliestTime);
		auto greedyTime = greedyBus.GetFirstDepartureAfter(earliestTime);
		if (bTime < greedyTime) {
			greedyBus = b;
		}
	}

	return greedyBus;
}

long long Problem::GetMatchingTime() const
{

}

int Bus::GetFirstDepartureAfter(int time) const
{
	auto quotient = time / id;

	return time % id == 0 ? quotient * id : quotient * id + id;
}
