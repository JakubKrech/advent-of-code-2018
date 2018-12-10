#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//#include <chrono>
//#include <thread>

struct PointOfLight
{
	int x, y;
	int x_velocity;
	int y_velocity;

	void update()
	{
		x += x_velocity;
		y += y_velocity;
	}
};

void get_input_from_file(std::string, std::vector<PointOfLight>&);

void apply_velocity(std::vector<PointOfLight>&);

int main()
{
	std::vector<PointOfLight> points;
	get_input_from_file("input.txt", points);

	apply_velocity(points);

	system("pause");
	return 0;
}

void apply_velocity(std::vector<PointOfLight>& points)
{
	int iteration_number = 0;

	for (int z = 0; z < 10831; z++) {
		iteration_number++;

		int x_max = points[0].x;
		int y_max = points[0].y;
		int x_min = points[0].x;
		int y_min = points[0].y;

		for (auto &x : points)
		{
			x.update();

			if (x.x > x_max) x_max = x.x;
			if (x.y > y_max) y_max = x.y;
			if (x.x < x_min) x_min = x.x;
			if (x.y < y_min) y_min = x.y;
		}

		if (iteration_number % 1000 == 0)
			std::cout << "Second #" << iteration_number << "  Size: " << x_max - x_min + 1 << " x " << y_max - y_min + 1 << "\n";

		if (abs(x_max-x_min) < 100 && abs(y_max-y_min) < 100) {
			std::cout << "Second #" << iteration_number << "  Size: " << x_max - x_min + 1 << " x " << y_max - y_min + 1 << "\n";

			std::vector<std::vector<char>> matrix;
			matrix.resize(x_max - x_min + 1, std::vector<char>(y_max - y_min + 1, '-'));

			for (auto x : points) matrix[abs(x.x - x_min)][abs(x.y - y_min)] = 'x';

			for (int i = 0; i < y_max - y_min + 1; i++) {
				for (int j = 0; j < x_max - x_min + 1; j++) {
					std::cout << matrix[j][i];
				}
				std::cout << "\n";
			}

			//std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		}
	}
}

void get_input_from_file(std::string file_name, std::vector<PointOfLight>& points)
{
	std::ifstream input_file(file_name);
	if (input_file.is_open()) {
		for (std::string str; std::getline(input_file, str); )
		{
			std::string posi = str.substr(0, str.find("velocity") - 1);
			std::string velo = str.substr(str.find("velocity"), str.length());

			points.push_back(PointOfLight{
				std::stoi(posi.substr(str.find("<") + 1, str.find(","))),
				std::stoi(posi.substr(str.find(",") + 1, str.find(">"))),
				std::stoi(velo.substr(velo.find("<") + 1, velo.find(","))),
				std::stoi(velo.substr(velo.find(",") + 1, velo.find(">")))
			});
		}
	}
	else std::cout << "Error while opening input file!\n\n";
	input_file.close();
}