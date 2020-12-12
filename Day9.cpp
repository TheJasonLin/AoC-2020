#include "Day9.h"

void Day9::Run()
{
	auto numbers = GetNumbers();
	auto outlier = FindOutlier(numbers);
	cout << "Outlier: " << outlier << endl;

	PrintContiguous(numbers, outlier);
}

vector<long long> Day9::GetNumbers()
{
	return InputParser::GetLongLongs("9.txt");
}

long long Day9::FindOutlier(vector<long long> numbers)
{
	static const int preambleSize = 25;

	for (int i = preambleSize; i < numbers.size(); i++) {
		auto number = numbers[i];

		// Create Set of candidates
		set<int> candidates;
		for (int j = i - preambleSize; j < i; j++) {
			candidates.insert(numbers[j]);
		}

		bool valid = false;

		// Check for a valid pair
		for (auto c : candidates) {
			auto match = number - c;
			if (candidates.find(match) != candidates.end()) {
				valid = true;
				continue;
			}
		}

		if (!valid) {
			return number;
		}
	}

	return -1;
}

void Day9::PrintContiguous(vector<long long> numbers, long long outlier)
{
	int minIndex = -1;
	int maxIndex = -1;
	for (int i = 0; i < numbers.size(); i++) {
		long long sum = numbers[i];
		for (int j = i + 1; j < numbers.size(); j++) {
			sum += numbers[j];
			if (sum == outlier) {
				minIndex = i;
				maxIndex = j;
				goto Found;
			}
			if (sum > outlier) {
				break;
			}
		}
	}

Found:
	int minValue = numbers[minIndex];
	int maxValue = numbers[minIndex];

	for (int i = minIndex; i <= maxIndex; i++) {
		auto num = numbers[i];
		minValue = num < minValue ? num : minValue;
		maxValue = num > maxValue ? num : maxValue;
	}

	cout << minValue << " + " << maxValue << " = " << minValue + maxValue << endl;
}
