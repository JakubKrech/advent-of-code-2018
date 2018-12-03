#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <ctime>

int part_one(const std::vector<int>&);
int part_two(const std::vector<int>&);

int main()
{
	std::ifstream input_file("input.txt");
	std::vector<int> data;
	if (input_file.is_open()) {
		for (std::string str; std::getline(input_file, str); ) {
			data.push_back(std::stoi(str));
		}
	}
	input_file.close();

	std::cout << "Part One:: " << part_one(data) << "\n";

	clock_t begin = clock();
	std::cout << "\nPart Two:: " << part_two(data) << "\n";
	clock_t end = clock();
	std::cout << double(end - begin) / CLOCKS_PER_SEC << "\n";

	system("pause");
	return 0;
}

int part_one(const std::vector<int> &data)
{
	std::ifstream input_file("input.txt");

	int frequency = 0;

	for (auto const &x : data)
		frequency += x;	

	return frequency;
}

int part_two(const std::vector<int> &data)
{
	int frequency = 0;
	std::unordered_set<int> previous_frequencies{ };

	for (int i = 0; ; i++) {
		for (auto const &x : data) {
			if (previous_frequencies.insert(frequency += x).second == false)
			{
				std::cout << "\nSIZE: " << previous_frequencies.size() << " LOOPS: " << i << "\n";
				return frequency;
			}
		}
	}
}