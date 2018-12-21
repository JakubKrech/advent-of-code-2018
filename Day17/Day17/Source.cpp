#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void get_input_from_file(std::string file_name, std::vector<std::vector<char>>&, int&, int&, int&);

bool left_side_limited(const std::vector<std::vector<char>>&, int, int);
bool right_side_limited(const std::vector<std::vector<char>>&, int, int);
void fill_limited_level(std::vector<std::vector<char>>&, int, int);
void fill_unlimited_level(std::vector<std::vector<char>>&, std::vector<std::pair<int, int>>&, int, int);
bool level_already_filled(const std::vector<std::vector<char>>& data, int x, int y);

int main()
{
	std::vector<std::vector<char>> data;
	int x_max;
	int y_max, y_min;

	get_input_from_file("input.txt", data, x_max, y_max, y_min);

	int spring_x = 500 + 3;
	int spring_y = 0;

	std::vector<std::pair<int, int>> fluid_instances;
	fluid_instances.push_back(std::make_pair(spring_x, spring_y + 1));

	while (!fluid_instances.empty())
	{
		for(auto fluid = fluid_instances.begin();;){

			if (fluid->second > y_max - 1) {
				data[fluid->first][fluid->second] = '|';
				fluid_instances.erase(fluid);
				break;
			}
			else if(data[fluid->first][fluid->second + 1] == '|') {
				data[fluid->first][fluid->second] = '|';
				fluid_instances.erase(fluid);
				break;
			}
			else if (data[fluid->first][fluid->second + 1] == '.') {
				data[fluid->first][fluid->second] = '|';
				fluid->second++;
			}
			else {
				if (left_side_limited(data, fluid->first, fluid->second) && 
					right_side_limited(data, fluid->first, fluid->second)) {
					if (level_already_filled(data, fluid->first, fluid->second)) {
						data[fluid->first][fluid->second] = '~';
						fluid->second -= 1;
					} 
					else {
						fill_limited_level(data, fluid->first, fluid->second);
						int xx = fluid->first; int yy = fluid->second;
						fluid_instances.erase(fluid);
						fluid_instances.push_back(std::make_pair(xx, yy - 1));
						break;
					}
				}
				else {
					int xx = fluid->first; int yy = fluid->second;
					fluid_instances.erase(fluid);
					fill_unlimited_level(data, fluid_instances, xx, yy);
					break;
				}
			}
		}
	}

	int tiles_reached_by_water = 0;
	int tiles_with_retained_water = 0;
	for (int i = y_min; i <= y_max; i++) {
		for (int j = 0; j < data.size(); j++) {
			if(data[j][i] == '~' || data[j][i] == '|') tiles_reached_by_water++;
			if (data[j][i] == '~') tiles_with_retained_water++;
		}
	}

	std::ofstream myfile("result.txt");
	for (int i = y_min; i <= y_max; i++) {
		for (int j = 0; j < data.size(); j++) {
			myfile << data[j][i];
		}
		myfile << "\n";
	}

	std::cout << "Tiles reached by water: " << tiles_reached_by_water << "\n";
	std::cout << "Tiles with retained water: " << tiles_with_retained_water << "\n\n";

	system("pause");
	return 0;
}

void get_input_from_file(std::string file_name, std::vector<std::vector<char>>& data,
	int& x_m, int& y_m, int& y_mi)
{
	std::ifstream input_file(file_name);
	if (input_file.is_open()) {
		std::vector<std::pair<int, int>> clay_squares;

		int x_max = 0;
		int y_max = 0;
		int y_min = 2147483647;

		for (std::string str; std::getline(input_file, str); )
		{
			if (str[0] == 'x') {
				int x = stoi(str.substr(2, str.find(',') - 2));
				if (x > x_max) x_max = x;

				int y_start = stoi(str.substr(str.find("y=") + 2, str.find("..") - str.find("y=") + 2));
				int y_end = stoi(str.substr(str.find("..") + 2, str.length() - str.find("..") + 2));

				std::vector<int> y_coords;
				for (int i = y_start; i <= y_end; i++) {
					y_coords.push_back(i);
					if (i > y_max) y_max = i;
					if (i < y_min) y_min = i;
				}

				for (auto y : y_coords) {
					clay_squares.push_back(std::make_pair(x, y));
				}
			}
			else
			{
				int y = stoi(str.substr(2, str.find(',') - 2));
				if (y > y_max) y_max = y;
				if (y < y_min) y_min = y;

				int x_start = stoi(str.substr(str.find("x=") + 2, str.find("..") - str.find("x=") + 2));
				int x_end = stoi(str.substr(str.find("..") + 2, str.length() - str.find("..") + 2));

				std::vector<int> x_coords;
				for (int i = x_start; i <= x_end; i++) {
					x_coords.push_back(i);
					if (i > x_max) x_max = i;
				}

				for (auto x : x_coords) {
					clay_squares.push_back(std::make_pair(x, y));
				}
			}
		}

		data.resize(x_max + 6, std::vector<char>(y_max + 2, '.'));

		for (auto &clay : clay_squares) {
			data[clay.first + 3][clay.second] = '#';
		}

		data[500 + 3][0] = '+';

		x_m = x_max;
		y_m = y_max;
		y_mi = y_min;
	}
	else std::cout << "Error while opening input file!\n\n";
	input_file.close();
}

bool left_side_limited(const std::vector<std::vector<char>>& data, int x, int y) {

	for (;;) {
		if (data[x - 1][y] != '#') {
			x--;
			if (data[x][y + 1] == '.') return false;
		}
		else return true;
	}
}

bool right_side_limited(const std::vector<std::vector<char>>& data, int x, int y) {

	for (;;) {
		if (data[x + 1][y] != '#') {
			x++;
			if (data[x][y + 1] == '.') return false;
		}
		else return true;
	}
}

void fill_limited_level(std::vector<std::vector<char>>& data, int x, int y) {

	data[x][y] = '~';

	int left_x = x;
	int left_y = y;
	while (data[left_x - 1][left_y] != '#') {
		data[left_x][left_y] = '~';
		left_x--;
	}
	data[left_x][left_y] = '~';

	int right_x = x;
	int right_y = y;
	while (data[right_x + 1][right_y] != '#') {
		data[right_x][right_y] = '~';
		right_x++;
	}
	data[right_x][right_y] = '~';
}

void fill_unlimited_level(std::vector<std::vector<char>>& data,
	std::vector<std::pair<int, int>>& fluid_instances, int x, int y) {

	int left_x = x;
	int left_y = y;

	while (data[left_x - 1][left_y] != '#') {
		data[left_x][left_y] = '|';
		left_x--;
		if (data[left_x][left_y + 1] == '|') {
			data[left_x][left_y] = '|';
			break;
		}
		else if (data[left_x][left_y + 1] == '.') {
			data[left_x][left_y] = '|';
			fluid_instances.push_back(std::make_pair(left_x, left_y + 1));
			break;
		}
	}
	data[left_x][left_y] = '|';

	int right_x = x;
	int right_y = y;

	while (data[right_x + 1][right_y] != '#') {
		data[right_x][right_y] = '|';
		right_x++;
		if (data[right_x][right_y + 1] == '|') {
			data[right_x][right_y] = '|';
			break;
		}
		else if (data[right_x][right_y + 1] == '.') {
			data[right_x][right_y] = '|';
			fluid_instances.push_back(std::make_pair(right_x, right_y + 1));
			break;
		}
	}
	data[right_x][right_y] = '|';
}

bool level_already_filled(const std::vector<std::vector<char>>& data, int x, int y) {
	int left_x = x;
	int left_y = y;
	while (data[left_x - 1][left_y] != '#') {
		left_x--;
		if (data[left_x][left_y] != '~') return false;
	}

	while (data[x + 1][y] != '#') {
		x++;
		if (data[left_x][left_y] != '~') return false;
	}
	return true;
}