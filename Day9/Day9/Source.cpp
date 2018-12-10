#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>

void get_input_from_file(std::string, int&, int&);

long long find_winning_player_score(int, int);

int main()
{
	int number_of_players;
	int final_marble_value;
	get_input_from_file("input.txt", number_of_players, final_marble_value);

	std::cout << "Part One: " << find_winning_player_score(number_of_players, final_marble_value) << "\n";

	std::cout << "Part Two: " << find_winning_player_score(number_of_players, final_marble_value * 100) << "\n\n";

	system("pause");
	return 0;
}

long long find_winning_player_score(int number_of_players, int final_marble_value)
{
	std::list<int> marbles{ 0,2,1 };
	std::vector<long long> players(number_of_players, 0);

	std::list<int>::iterator current_marble = marbles.begin();
	current_marble++;
	int current_player = 2;

	for (int current_marble_value = 3; current_marble_value <= final_marble_value; current_marble_value++) {
		if (current_marble_value % 23 != 0) {
			std::list<int>::iterator new_marble = current_marble;

			for (int x = 0; x < 2; x++) {
				if (new_marble != marbles.end())
					new_marble++;
				else {
					new_marble = marbles.begin();
					new_marble++;
				}
			}
			current_marble = marbles.insert(new_marble, current_marble_value);
		}
		else {
			players[current_player] += current_marble_value;

			std::list<int>::iterator marble_to_erase = current_marble;

			for (int x = 0; x < 7; x++) {
				if (marble_to_erase != marbles.begin())
					marble_to_erase--;
				else {
					marble_to_erase = marbles.end();
					marble_to_erase--;
				}
			}
			players[current_player] += *marble_to_erase;

			current_marble = marbles.erase(marble_to_erase);
		}

		(current_player == number_of_players - 1) ? (current_player = 0) : (current_player++);
	}
	

	long long max_player_score = 0;
	for (auto x : players)
		if (x > max_player_score) max_player_score = x;

	return max_player_score;
}

void get_input_from_file(std::string file_name, int& number_of_players, int& final_marble_value)
{
	std::ifstream input_file(file_name);
	if (input_file.is_open()) {
		for (std::string str; std::getline(input_file, str); )
		{
			number_of_players = std::stoi(str.substr(0, str.find("players") - 1));
			final_marble_value = std::stoi(str.substr(str.find("worth") + 6, str.find("points") - 1));
		}
	}
	else std::cout << "Error while opening input file!\n\n";
	input_file.close();
}