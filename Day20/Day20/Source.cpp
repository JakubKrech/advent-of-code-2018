#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Room
{
	int x, y;
	int distance;
};

void get_input_from_file(std::string file_name, std::string&);
void find_room(std::string, std::vector<Room>&, int, int, int, int&);

int main()
{
	std::string input;
	std::vector<Room> rooms;

	get_input_from_file("input.txt", input);

	int start_x = 0;
	int start_y = 0;
	int counter = 0;
	int input_iterator = 0;
	find_room(input, rooms, start_x, start_y, counter, input_iterator);
	
	int max_dist = 0;
	int distance_over_1000 = 0;
	
	for (auto x : rooms) {
		if (x.distance > max_dist) {
			max_dist = x.distance;
		}
		if (x.distance >= 1000) distance_over_1000++;
	}

	std::cout << "Part 1: " << max_dist << "\n";
	std::cout << "Part 2: " << distance_over_1000 << "\n\n";

	system("pause");
	return 0;
}

void get_input_from_file(std::string file_name, std::string& input)
{
	std::ifstream input_file(file_name);
	if (input_file.is_open()) {
		for (std::string str; std::getline(input_file, str); )
		{
			input = str.substr(1, str.length() - 2);
		}	
	}
	else std::cout << "Error while opening input file!\n\n";
	input_file.close();
}

void find_room(std::string input, std::vector<Room>& rooms, int x, int y, int distance, int& input_iterator)
{	
	int init_x = x;
	int init_y = y;
	int init_d = distance;

	while (input_iterator < input.length()) {

		if (input[input_iterator] == ')') {
			input_iterator++;
			break;
		}
		else if (input[input_iterator] == '|') {
			input_iterator++;
			x = init_x;
			y = init_y;
			distance = init_d;
			continue;
		}

		if (input[input_iterator] == 'N') y++;
		else if (input[input_iterator] == 'E') x++;
		else if (input[input_iterator] == 'S') y--;
		else if (input[input_iterator] == 'W') x--;

		if (input[input_iterator] == 'N' || input[input_iterator] == 'E' ||
			input[input_iterator] == 'S' || input[input_iterator] == 'W') {
			
			bool already_present = false;

			for (auto room = rooms.begin(); room != rooms.end(); room++) {
				if (room->x == x && room->y == y) already_present = true;
			}

			if (!already_present) {
				rooms.push_back({ x, y, ++distance });
			}
		}

		int new_x = x;
		int new_y = y;
		int init_dist = distance;

		if (input[input_iterator] == '(') {
			find_room(input, rooms, new_x, new_y, init_dist, ++input_iterator);
		}	
		else {
			input_iterator++;
		}
	}
}