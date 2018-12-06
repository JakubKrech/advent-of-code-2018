#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Coord
{
	int id, x, y;
	int area = 0;
	bool infinite;
};

void get_input_from_file(std::string, std::vector<Coord>&);
int find_largest_area(std::vector<Coord>&);
int find_coordinates_within_given_total_distance(std::vector<Coord>&);

int main()
{
	std::vector<Coord> coordinates_;
	get_input_from_file("input.txt", coordinates_);

	std::cout << "Part One: " << find_largest_area(coordinates_) << "\n";

	std::cout << "Part Two: " << find_coordinates_within_given_total_distance(coordinates_) << "\n\n";

	system("pause");
	return 0;
}


int find_largest_area(std::vector<Coord>& coordinates_)
{
	for (auto &x : coordinates_) {
		bool left = false;
		bool top = false;
		bool right = false;
		bool bottom = false;

		for (auto &y : coordinates_) {
			if (y.x < x.x && abs(y.x - x.x) >= abs(y.y - x.y)) left = true;
			if (y.y > x.y && abs(y.y - x.y) >= abs(y.x - x.x)) top = true;
			if (y.x > x.x && abs(y.x - x.x) >= abs(y.y - x.y)) right = true;
			if (y.y < x.y && abs(y.y - x.y) >= abs(y.x - x.x)) bottom = true;
		}

		if (left && top && right && bottom) x.infinite = false;
		else x.infinite = true;
	}

	int grid_dimension_x = 0;
	int grid_dimension_y = 0;

	for (auto x : coordinates_) {
		if (x.x > grid_dimension_x) grid_dimension_x = x.x;
		if (x.y > grid_dimension_y) grid_dimension_y = x.y;
	}

	for (int i = 0; i <= grid_dimension_x; i++) {
		for (int j = 0; j <= grid_dimension_y; j++) {
			int closest_location_distance = grid_dimension_x + grid_dimension_y;
			int closest_location_id;

			for (auto x : coordinates_) {
				if ((abs(i - x.x) + abs(j - x.y)) < closest_location_distance) {
					closest_location_id = x.id;
					closest_location_distance = abs(i - x.x) + abs(j - x.y);
				}
				else if ((abs(i - x.x) + abs(j - x.y)) == closest_location_distance) {
					closest_location_id = -1;
				}
			}
			if (closest_location_id != -1) {
				coordinates_[closest_location_id].area++;
			}
		}
	}

	int largest_area = 0;
	for (auto x : coordinates_) {
		if (x.infinite == false) {
			if (x.area > largest_area) largest_area = x.area;
		}
	}
	return largest_area;
}

int find_coordinates_within_given_total_distance(std::vector<Coord>& coordinates_)
{
	int grid_dimension_x = 0;
	int grid_dimension_y = 0;

	for (auto x : coordinates_) {
		if (x.x > grid_dimension_x) grid_dimension_x = x.x;
		if (x.y > grid_dimension_y) grid_dimension_y = x.y;
	}

	int number_of_coordinates_within_given_distance = 0;

	for (int i = 0; i <= grid_dimension_x; i++) {
		for (int j = 0; j <= grid_dimension_y; j++) {
			
			int total_distance = 0;

			for (auto x : coordinates_) {
				total_distance += (abs(i - x.x) + abs(j - x.y));
			}
			
			if (total_distance < 10000) number_of_coordinates_within_given_distance++;
		}
	}
	return number_of_coordinates_within_given_distance;
}

void get_input_from_file(std::string file_name, std::vector<Coord>& target_object)
{
	std::ifstream input_file(file_name);
	if (input_file.is_open()) {
		int i = 0;
		for (std::string str; std::getline(input_file, str); ) {
			target_object.push_back({
				i++,
				std::stoi(str.substr(0, str.find(","))),
				std::stoi(str.substr(str.find(",") + 1, str.length()))
			});
		}
	}
	else std::cout << "Error while opening input file!\n\n";
	input_file.close();
}