#include "Day4.h"

vector<string> Passport::fields = {
	"byr",
	"iyr",
	"eyr",
	"hgt",
	"hcl",
	"ecl",
	"pid"
	// just ignore cid
};

Passport::Passport(string input):
	source(input)
{
	for (auto key : fields) {
		string regexString = "[a-z:0-9 #]*" + key + ":([#a-zA-Z0-9]+) [a-z:0-9 #]*";
		auto e = regex(regexString);
		if (!regex_match(source, e)) {
			continue;
		}
		auto value = regex_replace(source, regex(regexString), string("$1"));
		data.insert({ key, value });
	}
}

bool Passport::IsNumberValid(string key, int min, int max)
{
	if (data.find(key) == data.end()) {
		return false;
	}

	int value = stoi(data[key]);

	return value >= min && value <= max;
}

Height Passport::GetHeight()
{
	static auto e = regex("([0-9]+)(in|cm)");
	string s = data["hgt"];

	if (!regex_match(s, e)) {
		return Height();
	}

	auto valueStr = regex_replace(s, e, string("$1"));
	auto unitStr = regex_replace(s, e, string("$2"));
	
	auto value = stoi(valueStr);

	bool metric;
	if (unitStr == "cm") {
		metric = true;
	}
	else if (unitStr == "in") {
		metric = false;
	}
	else {
		return Height();
	}

	return Height(metric, value);
}

bool Passport::IsHairColorValid()
{
	auto e = regex("^#[a-z0-9]{6}$");
	auto s = data["hcl"];
	return regex_match(s, e);
}

bool Passport::IsEyeColorValid()
{
	auto e = regex("^(amb|blu|brn|gry|grn|hzl|oth)$");
	auto s = data["ecl"];
	return regex_match(s, e);
}

bool Passport::IsPassportIDValid()
{
	auto e = regex("^[0-9]{9}$");
	auto s = data["pid"];
	return regex_match(s, e);
}

void Day4::Run()
{
	auto passports = GetInputs();

	int validCount = 0;

	for (auto p : passports) {
		if (p.data.size() == Passport::fields.size()) {
			validCount++;
		}
	}

	cout << validCount << endl;
}

void Day4::Run2()
{
	auto passports = GetInputs();

	int validCount = 0;

	for (auto p : passports) {
		if (p.data.size() != Passport::fields.size()) {
			continue;
		}

		if (!p.IsNumberValid("byr", 1920, 2002)) {
			continue;
		}

		if (!p.IsNumberValid("iyr", 2010, 2020)) {
			continue;
		}

		if (!p.IsNumberValid("eyr", 2020, 2030)) {
			continue;
		}

		auto height = p.GetHeight();
		if (!height.valid) {
			continue;
		}

		if (height.metric && (height.value < 150 || height.value > 193)) {
			continue;
		}
		if (!height.metric && (height.value < 59 || height.value > 76)) {
			continue;
		}

		if (!p.IsHairColorValid()) {
			continue;
		}

		if (!p.IsEyeColorValid()) {
			continue;
		}

		if (!p.IsPassportIDValid()) {
			continue;
		}

		// Print Valid ones for debugging
		cout << p.source << endl;
		validCount++;
	}

	cout << validCount << endl;
}

vector<Passport> Day4::GetInputs()
{
	vector<Passport> out;

	string buffer = "";
	auto strings = InputParser::GetStrings("day4.txt");
	for (auto s : strings) {
		if (s.size() == 0) {
			auto p = Passport(buffer);
			out.push_back(p);
			buffer = "";
		}
		else {
			buffer += s + " ";
		}
	}

	// last entry has no newline
	auto p = Passport(buffer);
	out.push_back(p);

	return out;
}
