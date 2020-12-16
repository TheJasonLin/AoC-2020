#include "Day15.h"

void Day15::Run()
{
	auto seeds = InputParser::GetInts("15.txt");

	Game g(seeds);

	for (int i = 1; i < 10; i++) {
		cout << i << ":" << g.GetNumber(i) << endl;
	}
	cout << "2020: " << g.GetNumber(30000000) << endl;
}

int Game::GetNumber(int n)
{
	map<int, int> cache;
	cache.empty();
	int num = seeds[0];
	int lastTime = -1;
	for (int i = 0; i < n; i++) {
		if (i < seeds.size()) {
			num = seeds[i];
		}
		else {
			if (lastTime == -1) {
				num = 0;
			}
			else {
				num = i - 1 - lastTime;
			}
		}

		if (cache.find(num) == cache.end()) {
			lastTime = -1;
		}
		else {
			lastTime = cache[num];
		}
		cache[num] = i;
	}

	return num;
}
