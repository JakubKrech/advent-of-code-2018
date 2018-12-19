#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#define minutes 1000

void get_input_from_file(std::string file_name, std::vector<std::vector<char>>& acre);

int main()
{
	std::vector<std::vector<char>> acre;
	acre.resize(50, std::vector<char>(50, 0));
	get_input_from_file("input.txt", acre);

	int prev_value = 0;

	for (int m = 0; m < minutes; m++)
	{	
		std::vector<std::vector<char>> new_acre = acre;

		for (int i = 0; i < acre.size(); i++)
		{
			for (int j = 0; j < acre[0].size(); j++)
			{
				int sum_of_trees = 0;
				int sum_of_lumb = 0;

				if (i - 1 >= 0) {
					if (acre[i - 1][j] == '|')sum_of_trees++;
					else if (acre[i - 1][j] == '#')sum_of_lumb++;
				}

				if (i + 1 < acre.size()) {
					if (acre[i + 1][j] == '|')sum_of_trees++;
					else if (acre[i + 1][j] == '#')sum_of_lumb++;
				}

				if (j - 1 >= 0) {
					if (acre[i][j - 1] == '|')sum_of_trees++;
					else if (acre[i][j - 1] == '#')sum_of_lumb++;
				}

				if (j + 1 < acre.size()) {
					if (acre[i][j + 1] == '|')sum_of_trees++;
					else if (acre[i][j + 1] == '#')sum_of_lumb++;
				}

				if (i + 1 < acre.size() && j + 1 < acre.size()) {
					if (acre[i + 1][j + 1] == '|')sum_of_trees++;
					else if (acre[i + 1][j + 1] == '#')sum_of_lumb++;
				}

				if (i - 1 >= 0 && j - 1 >= 0) {
					if (acre[i - 1][j - 1] == '|')sum_of_trees++;
					else if (acre[i - 1][j - 1] == '#')sum_of_lumb++;
				}

				if (i + 1 < acre.size() && j - 1 >= 0) {
					if (acre[i + 1][j - 1] == '|')sum_of_trees++;
					else if (acre[i + 1][j - 1] == '#')sum_of_lumb++;
				}

				if (i - 1 >= 0 && j + 1 < acre.size()) {
					if (acre[i - 1][j + 1] == '|')sum_of_trees++;
					else if (acre[i - 1][j + 1] == '#')sum_of_lumb++;
				}

				if (acre[i][j] == '.' && sum_of_trees >= 3)new_acre[i][j] = '|';
				else if (acre[i][j] == '|' && sum_of_lumb >= 3)new_acre[i][j] = '#';
				else if (acre[i][j] == '#' && (sum_of_trees < 1 || sum_of_lumb < 1)) new_acre[i][j] = '.';
			}
		}
		acre = std::move(new_acre);
		
		system("CLS"); //just to create some kind of visualization
		for (int i = 0; i < acre.size(); i++)
		{
			for (int j = 0; j < acre[0].size(); j++)
			{
				std::cout << acre[i][j];
			}
			std::cout << "\n";
		}

		int total_wooden_acres = 0;
		int total_lumberyeards = 0;
		for (int i = 0; i < acre.size(); i++)
		{
			for (int j = 0; j < acre[0].size(); j++)
			{
				if (acre[i][j] == '|') total_wooden_acres++;
				else if (acre[i][j] == '#') total_lumberyeards++;
			}
		}
		std::cout << m + 1 << " " << total_wooden_acres*total_lumberyeards << " " << total_wooden_acres*total_lumberyeards - prev_value << "\n";
		prev_value = total_wooden_acres*total_lumberyeards;
	}
	
	// Part 2:
	// After some time result changes become regular
	// #900 = 184960
	// #928 = 184960
	// #956 = 184960
	// etc. step = 28
	// (1000000000 - 900) / 28 = 35714253,5714...
	// 35714253 * 28 = 999999084
	// 999999084 + 900 = 999999984
	// 1000000000 - 999999984 = 16
	// 900 + 16 = 916 
	// This gives us an answer, resource value at minute 916 is the same as at minute 1000000000

	system("pause");
	return 0;
}

void get_input_from_file(std::string file_name, std::vector<std::vector<char>>& acre)
{
	std::ifstream input_file(file_name);
	if (input_file.is_open()) {
		
		int i = 0;
		for (std::string str; std::getline(input_file, str); i++ )
		{
			for (int j = 0; j < str.length(); j++)
			{
				acre[i][j] = str[j];
			}
		}
	
	}
	else std::cout << "Error while opening input file!\n\n";
	input_file.close();
}