#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <chrono>
#include <thread>

struct Room
{
	int x, y;
	int distance;

	friend std::ostream& operator<<(std::ostream& out, const Room& a) {
		out << a.x << "," << a.y << " dist: " << a.distance << "\n";
		return out;
	}
};

void get_input_from_file(std::string file_name, std::string&);
void find_room(std::string, std::vector<Room>&, int, int, int, int&);

int main()
{
	std::string input;
	std::vector<Room> rooms;

	get_input_from_file("input_test.txt", input);

	std::cout << input << "\n\n";
	std::cout << "Input size: " << input.length() << "\n\n";

	int start_x = 0;
	int start_y = 0;
	int counter = 0;
	int input_counter = 0;
	find_room(input, rooms, start_x, start_y, counter, input_counter);
	
	int max_dist = 0;
	int max_x, max_y;
	for (auto x : rooms)
		if (x.distance > max_dist) {
			max_dist = x.distance;
			max_x = x.x;
			max_y = x.y;
		}
	std::cout << "\n\nMax dist: " << max_dist << "\n";
	
	for (auto x : rooms)
		if (x.x == max_x && x.y == max_y) {
			std::cout << x.x << " " << x.y << " " << x.distance << "\n";
		}

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

void find_room(std::string input, std::vector<Room>& rooms, int x, int y, int distance, int& input_counter)
{
	//std::cout << "FIND_ROOM x,y:" << x << "," << y << "  input_counter:" << input_counter << "\n";
		
	int new_x = x;
	int new_y = y;

	while (input_counter < input.length()) {

		if (input[input_counter] == ')') {
			input_counter++;
			continue;
		}
		else if (input[input_counter] == '|') {
			//find_room(input, rooms, new_x, new_y, init_dist, ++input_counter);
			input_counter++;
			break;
		}

		if (input[input_counter] == 'N') y++;
		else if (input[input_counter] == 'E') x++;
		else if (input[input_counter] == 'S') y--;
		else if (input[input_counter] == 'W') x--;

		if (input[input_counter] == 'N' || input[input_counter] == 'E' ||
			input[input_counter] == 'S' || input[input_counter] == 'W') {
			bool already_present = false;

			for (auto z = rooms.begin(); z != rooms.end(); z++) {
				if (z->x == x && z->y == y) already_present = true;
			}

			if (!already_present) {
				rooms.push_back({ x, y, ++distance });
				//std::cout << "   " << rooms[rooms.size() - 1];
			}
		}

		int init_dist = distance;

		if (input[input_counter] == '(') {
			find_room(input, rooms, x, y, init_dist, ++input_counter);
		}	
		else {
			input_counter++;
		}
	}
}