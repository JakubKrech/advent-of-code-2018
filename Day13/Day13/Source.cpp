#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <vector>
#include <algorithm>

struct Cart
{
	int x, y;
	char direction;
	int turn_direction = 1;
	bool is_on_crossroad = false;
	bool is_on_right_corner = false; //   /
	bool is_on_left_corner = false;  //	  \

	bool crashed = false;

	Cart(int xx, int yy) : x(xx), y(yy) {};
	Cart(int xx, int yy, char d) : x(xx), y(yy), direction(d) {};

	void crossroad_encountered()
	{
		if (turn_direction == 1) {
			if (direction == '^') direction = '<';
			else if (direction == '>') direction = '^';
			else if (direction == 'v') direction = '>';
			else if (direction == '<') direction = 'v';
		}
		else if (turn_direction == 3) {
			if (direction == '^') direction = '>';
			else if (direction == '>') direction = 'v';
			else if (direction == 'v') direction = '<';
			else if (direction == '<') direction = '^';
		}
		turn_direction++;
		if (turn_direction > 3) turn_direction = 1;

		is_on_crossroad = true;
	}

	void corner_encountered(char corner)
	{
		if (corner == '/') {
			if (direction == '^') direction = '>';
			else if (direction == '>') direction = '^';
			else if (direction == 'v') direction = '<';
			else if (direction == '<') direction = 'v';

			is_on_right_corner = true;
		}
		else if (corner == '\\') {
			if (direction == '^') direction = '<';
			else if (direction == '>') direction = 'v';
			else if (direction == 'v') direction = '>';
			else if (direction == '<') direction = '^';

			is_on_left_corner = true;
		}
	}

	bool operator<(Cart a)
	{
		bool value = false;
		if (x < a.x) value = true;
		if (x > a.x) value = false;
		if (y < a.y) value = true;
		if (y > a.y) value = false;

		return value;
	}

	bool operator==(Cart a)
	{
		if (x == a.x && y == a.y) return true;
		else return false;
	}
};

void get_input_from_file(std::string, std::vector<std::vector<char>>&, std::vector<Cart>&);

void calculate_next_tick(std::vector<std::vector<char>>&, std::vector<Cart>&);
void analyze_path(std::vector<std::vector<char>>& paths, std::vector<Cart>& carts_, Cart& x);
bool is_cart(char);
bool is_crossroad(char);
bool is_corner(char);
void remove_crashed_carts(std::vector<std::vector<char>>&, std::vector<Cart>&, int, int);

int main()
{
	std::vector<std::vector<char>> paths;
	std::vector<Cart> carts_;
	get_input_from_file("input.txt", paths, carts_);

	while (carts_.size() > 1) {

		std::sort(carts_.begin(), carts_.end());
		calculate_next_tick(paths, carts_);

		for (int i = 0; i < carts_.size(); i++) {
			if (carts_[i].crashed) {
				carts_.erase(carts_.begin() + i);
				i--;
			}
		}
	}
	std::cout << "LAST CART LEFT: " << carts_[0].y << "," << carts_[0].x << "\n";

	system("pause");
	return 0;
}

void calculate_next_tick(std::vector<std::vector<char>>& paths, std::vector<Cart>& carts_)
{
	for (auto &x : carts_) {

		if (x.crashed) continue;

		bool straight_path = false;

		if (x.is_on_crossroad) {
			paths[x.x][x.y] = '+';
			x.is_on_crossroad = false;
		}
		else if (x.is_on_right_corner) {
			paths[x.x][x.y] = '/';
			x.is_on_right_corner = false;
		}
		else if (x.is_on_left_corner) {
			paths[x.x][x.y] = '\\';
			x.is_on_left_corner = false;
		}
		else straight_path = true;


		if (x.direction == '^') {
			if (straight_path) paths[x.x][x.y] = '|';
			x.x--;
			analyze_path(paths, carts_, x);
		}
		else if (x.direction == '>') {

			if (straight_path) paths[x.x][x.y] = '-';
			x.y++;
			analyze_path(paths, carts_, x);
		}
		else if (x.direction == 'v') {
			if (straight_path) paths[x.x][x.y] = '|';
			x.x++;
			analyze_path(paths, carts_, x);
		}
		else if (x.direction == '<') {
			if (straight_path) paths[x.x][x.y] = '-';
			x.y--;
			analyze_path(paths, carts_, x);
		}
	}
}

void analyze_path(std::vector<std::vector<char>>& paths, std::vector<Cart>& carts_, Cart& x) {
	if (!is_cart(paths[x.x][x.y])) {
		if (is_crossroad(paths[x.x][x.y])) {
			x.crossroad_encountered();
			paths[x.x][x.y] = x.direction;
		}
		else if (is_corner(paths[x.x][x.y])) {
			x.corner_encountered(paths[x.x][x.y]);
			paths[x.x][x.y] = x.direction;
		}
		else {
			paths[x.x][x.y] = x.direction;
		}
	}
	else {
		std::cout << "--CRASH! " << x.x << "," << x.y << "\n";

		remove_crashed_carts(paths, carts_, x.x, x.y);
	}
}

bool is_cart(char a)
{
	if (a == '^' || a == '>' || a == 'v' || a == '<') return true;
	else return false;
}

bool is_crossroad(char a)
{
	if (a == '+') return true;
	else return false;
}

bool is_corner(char a)
{
	if (a == '/' || a == '\\') return true;
	else return false;
}

void remove_crashed_carts(std::vector<std::vector<char>>& paths, std::vector<Cart>& carts_, int x, int y)
{
	for (auto x : carts_) {
		//std::cout << " CART " << x.x << "," << x.y << " " << x.direction << "\n";
	}
	
	for (int i = 0; i < carts_.size(); i++) {
		if (carts_[i].x == x && carts_[i].y == y) {
			//std::cout << "  Removing " << carts_[i].x << "," << carts_[i].y << " " << carts_[i].direction << "\n";
			
			if (carts_[i].is_on_crossroad) {
				paths[carts_[i].x][carts_[i].y] = '+';
				carts_[i].is_on_crossroad = false;
			}
			else if (carts_[i].is_on_right_corner) {
				paths[carts_[i].x][carts_[i].y] = '/';
				carts_[i].is_on_right_corner = false;
			}
			else if (carts_[i].is_on_left_corner) {
				paths[carts_[i].x][carts_[i].y] = '\\';
				carts_[i].is_on_left_corner = false;
			}
			else {
				if (paths[x][y] == '^') paths[x][y] = '|';
				else if (paths[x][y] == '>') paths[x][y] = '-';
				else if (paths[x][y] == 'v') paths[x][y] = '|';
				else if (paths[x][y] == '<') paths[x][y] = '-';
			}
			carts_[i].crashed = true;
		}
	}
}

void get_input_from_file(std::string file_name, std::vector<std::vector<char>>& paths, std::vector<Cart>& carts_)
{
	std::ifstream input_file(file_name);
	if (input_file.is_open()) {
		int width = 0;
		int height = 0;

		for (std::string str; std::getline(input_file, str); )
		{
			height++;
			if (str.length() > width) width = str.length();
		}
		paths.resize(width, std::vector<char>(height, ' '));

		input_file.clear();
		input_file.seekg(0, input_file.beg);

		int i = 0;
		for (std::string str; std::getline(input_file, str); i++ )
		{
			for (int j = 0; j < str.length(); j++) {
				paths[i][j] = str[j];
				if (is_cart(str[j])) carts_.push_back({ i, j, str[j] });
			}
		}
	}
	else std::cout << "Error while opening input file!\n\n";
	input_file.close();
}