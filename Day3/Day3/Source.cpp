#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct FabricClaim
{
	int id;
	int left_padding;
	int top_padding;
	int width;
	int height;
};

int main()
{
	std::vector<FabricClaim> claims_;

	std::ifstream input_file("input.txt");
	if (input_file.is_open()) {
		for (std::string str; std::getline(input_file, str); ) 
		{
			claims_.push_back({
				std::stoi(str.substr(str.find("#") + 1, str.find("@") - 2 - str.find("#") + 1)),
				std::stoi(str.substr(str.find("@") + 2, str.find(",")     - str.find("@") + 2)),
				std::stoi(str.substr(str.find(",") + 1, str.find(":") - 1 - str.find(","))),
				std::stoi(str.substr(str.find(":") + 2, str.find("x")     - str.find(":") + 2)),
				std::stoi(str.substr(str.find("x") + 1, 2))
			});
		}
	}
	input_file.close();


	std::vector<std::vector<int>> fabric;
	fabric.resize(1000, std::vector<int>(1000, 0));

	int overlapped_inches = 0;
	int not_overlapped_claim_id = -1;

	for (const auto &x : claims_) {
		for (int i = x.left_padding; i < x.left_padding + x.width; i++) {
			for (int j = x.top_padding; j < x.top_padding + x.height; j++) {
				fabric[i][j]++;
			}
		}
	}

	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			if (fabric[i][j] > 1) overlapped_inches++;
		}
	}

	for (const auto &x : claims_) {
		bool overlapped = false;
		for (int i = x.left_padding; i < x.left_padding + x.width; i++) {
			for (int j = x.top_padding; j < x.top_padding + x.height; j++) {
				if (fabric[i][j] > 1) overlapped = true;
			}
		}
		if (overlapped == false) not_overlapped_claim_id = x.id;
	}

	std::cout << "Part One: " << overlapped_inches << "\n";
	std::cout << "Part Two: " << not_overlapped_claim_id << "\n";

	system("pause");
	return 0;
}