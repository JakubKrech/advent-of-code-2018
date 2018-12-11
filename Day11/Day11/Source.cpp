//this algorithm is not optimized, it could get vastly improved by applying this method https://en.wikipedia.org/wiki/Summed-area_table

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#define fuel_cells_grid_size 300

int find_cell_power_level(const int&, const int&, const int&);

int main()
{
	int serial_number = 3628;	//input

	std::vector<std::vector<int>> fuel_cells_grid;
	fuel_cells_grid.resize(fuel_cells_grid_size, std::vector<int>(fuel_cells_grid_size, 0));

	for (int x = 0; x < fuel_cells_grid_size; x++) {
		for (int y = 0; y < fuel_cells_grid_size; y++) {
			fuel_cells_grid[x][y] = find_cell_power_level(x, y, serial_number);
		}
	}

	int max_square_power = fuel_cells_grid[0][0];
	int max_square_x = 0;
	int max_square_y = 0;
	int square_size = 1;

	//for (int size = 3; size == 3; size++) {		//PART 1
	for (int size = 1; size < fuel_cells_grid_size; size++) {		//PART 2
		for (int y = 0; y + size - 1 < fuel_cells_grid_size; y++) {
			for (int x = 0; x + size - 1 < fuel_cells_grid_size; x++) {

				int square_power = 0;
				for (int i = 0; i < size; i++) {
					for (int j = 0; j < size; j++) {
						square_power += fuel_cells_grid[x + j][y + i];
					}
				}

				if (square_power > max_square_power) {
					max_square_power = square_power;
					max_square_x = x + 1;
					max_square_y = y + 1;
					square_size = size;
					std::cout << "NEW MAX -> " << x + 1 << "," << y + 1 << " value: " << square_power << " size: " << size << "\n";
				}
			}
		}
	}

	std::cout << "\nANSWER: " << max_square_x << "," << max_square_y << "," << square_size << "\n\n";

	system("pause");
	return 0;
}

int find_cell_power_level(const int& x, const int& y, const int& serial_number)
{
	/*
	int rack_id = (x + 1) + 10;
	int power_level = rack_id * (y + 1);
	int increased_p_l = power_level + serial_number;
	int mult_by_rack = increased_p_l * rack_id;
	int hundred_digit = (mult_by_rack / (int)pow(10, 2)) % 10;
	int final_power_level = hundred_digit - 5;
	*/

	return (((((((x + 1) + 10) * (y + 1)) + serial_number) * ((x + 1) + 10)) / (int)pow(10, 2)) % 10) - 5;
}
