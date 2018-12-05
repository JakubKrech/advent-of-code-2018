#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

void get_input_from_file(std::string, std::string&);
int react_polymer(std::string&);
void detect_problem_causing_type(const std::string&, int&, int&);

int main()
{
	std::string polymer;

	get_input_from_file("input.txt", polymer);
	
	std::cout << "Part One: " << react_polymer(polymer) << " units remain after fully reacting the polymer\n"; 
	
	int type_causing_problem;
	int polymer_length_after_problem_removal = polymer.length();

	detect_problem_causing_type(polymer, type_causing_problem, polymer_length_after_problem_removal);

	std::cout << "Part Two: we can produce shortest polymer of length " << polymer_length_after_problem_removal << " by removing type " << char(type_causing_problem) << "\n\n";

	system("pause");
	return 0;
}

int react_polymer(std::string& polymer)
{
	for (int i = 0; (i + 1) < polymer.length();) {
		if (int(polymer[i]) - int(polymer[i + 1]) == 32 || (int(polymer[i]) - int(polymer[i + 1]) == -32)) {
			polymer.erase(i, 2);
			if (i > 0) i--;
		}
		else i++;
	}
	//std::cout << polymer << "\n\n";
	return polymer.length();
}

void detect_problem_causing_type(const std::string& polymer, int& type_causing_problem, int& polymer_length_after_problem_removal)
{
	for (int i = 65; i <= 90; i++) {
		std::string polymer_temp = polymer;
		polymer_temp.erase(std::remove(polymer_temp.begin(), polymer_temp.end(), char(i)), polymer_temp.end());
		polymer_temp.erase(std::remove(polymer_temp.begin(), polymer_temp.end(), char(i + 32)), polymer_temp.end());

		int new_length_after_reacting = react_polymer(polymer_temp);

		//std::cout << char(i) << " " << new_length_after_reacting << "\n";

		if (new_length_after_reacting < polymer_length_after_problem_removal) {
			type_causing_problem = i;
			polymer_length_after_problem_removal = new_length_after_reacting;
		}
	}
}

void get_input_from_file(std::string file_name, std::string& target_object)
{
	std::ifstream input_file(file_name);
	if (input_file.is_open()) {
		std::getline(input_file, target_object);
	}
	else std::cout << "Error while opening input file!\n\n";
	input_file.close();
}