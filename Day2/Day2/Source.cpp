#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

int part_one(const std::vector<std::string>&);
std::string part_two(const std::vector<std::string>&);

int main()
{
	std::ifstream input_file("input.txt");
	std::vector<std::string> data;
	if (input_file.is_open()) {
		for (std::string str; std::getline(input_file, str); ) {
			data.push_back(str);
		}
	}
	input_file.close();

	std::cout << "Part One: " << part_one(data) << "\n";
	std::cout << "Part Two: " << part_two(data) << "\n";

	system("pause");
	return 0;
}

int part_one(const std::vector<std::string>& data)
{
	int double_occurences = 0;
	int triple_occurences = 0;

	for (auto str : data)
	{
		std::map<std::string, int> letters_count;

		for (int i = 0; i < str.length(); i++)
		{
			std::string letter = str.substr(i, 1);

			auto index = letters_count.find(letter);
			if (index == letters_count.end()) letters_count.insert({ letter, 1 });
			else index->second++;
		}

		bool double_existence = false;
		bool triple_existence = false;

		for (auto x : letters_count) {
			if (x.second == 2) double_existence = true;
			if (x.second == 3) triple_existence = true;
		}

		if (double_existence) double_occurences++;
		if (triple_existence) triple_occurences++;
	}
	std::cout << "double_occurences: " << double_occurences << "\n";
	std::cout << "triple_occurences: " << triple_occurences << "\n\n";
	return double_occurences * triple_occurences;
}

std::string part_two(const std::vector<std::string>& data)
{
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = i + 1; j < data.size(); j++)
		{
			int error_index = -1;
			for (int k = 0; k < data[i].length(); k++)
			{
				if (data[i].substr(k, 1) != data[j].substr(k, 1))
				{
					if (error_index == -1) error_index = k; // value -1 means that no error was found yet
					else {
						error_index = -2; // value -2 means that more than one errors were found
						break;
					}
				}
			}
			if (error_index != -1 && error_index != -2) {
				std::cout << "\nMatching ID: " << data[i] << "\nError index: " << error_index << "\n\n";
				std::string result = data[i];
				result.erase(error_index, 1);
				return result;
			}
		}
	}
}
