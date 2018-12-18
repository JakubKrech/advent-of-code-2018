#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

typedef std::vector<int> func(const std::vector<int>&, int, int, int, int);
typedef func* pfunc;

struct Sample
{
	std::vector<int> before;
	std::vector<int> instruction;
	std::vector<int> after;
};

std::vector<int> addr(const std::vector<int>&, int, int, int, int);
std::vector<int> addi(const std::vector<int>&, int, int, int, int);

std::vector<int> mulr(const std::vector<int>&, int, int, int, int);
std::vector<int> muli(const std::vector<int>&, int, int, int, int);

std::vector<int> banr(const std::vector<int>&, int, int, int, int);
std::vector<int> bani(const std::vector<int>&, int, int, int, int);

std::vector<int> borr(const std::vector<int>&, int, int, int, int);
std::vector<int> bori(const std::vector<int>&, int, int, int, int);

std::vector<int> setr(const std::vector<int>&, int, int, int, int);
std::vector<int> seti(const std::vector<int>&, int, int, int, int);

std::vector<int> gtir(const std::vector<int>&, int, int, int, int);
std::vector<int> gtri(const std::vector<int>&, int, int, int, int);
std::vector<int> gtrr(const std::vector<int>&, int, int, int, int);

std::vector<int> eqir(const std::vector<int>&, int, int, int, int);
std::vector<int> eqri(const std::vector<int>&, int, int, int, int);
std::vector<int> eqrr(const std::vector<int>&, int, int, int, int);

void get_input_from_file(std::string file_name, std::vector<Sample>& samples_);

int main()
{
	std::vector<Sample> samples_;
	get_input_from_file("input.txt", samples_);
	std::vector<pfunc> functions{ addr ,addi , mulr, muli, banr, bani, borr, bori, setr, seti, gtir, gtri, gtrr, eqir, eqri, eqrr };

	/*for (auto x : samples_) {
		std::cout << x.before[0] << " " << x.before[1] << " " << x.before[2] << " " << x.before[3] << " \n";
		std::cout << x.instruction[0] << " " << x.instruction[1] << " " << x.instruction[2] << " " << x.instruction[3] << " \n";
		std::cout << x.after[0] << " " << x.after[1] << " " << x.after[2] << " " << x.after[3] << " \n";
		std::cout << "\n";
	}*/

	int samples_behaving_correctly = 0;
	for (auto x : samples_) {
		int correct_behaviour_counter = 0;

		for (auto z : functions) {
			std::vector<int> result = z(x.before, x.instruction[0], x.instruction[1], x.instruction[2], x.instruction[3]);

			if (result[0] == x.after[0] && result[1] == x.after[1] && result[2] == x.after[2] && result[3] == x.after[3]) {
				correct_behaviour_counter++;
			}
		}

		if (correct_behaviour_counter >= 3) samples_behaving_correctly++;
	}

	std::cout << "Samples behaving correctly: " << samples_behaving_correctly << "\n";

	system("pause");
	return 0;
}

void get_input_from_file(std::string file_name, std::vector<Sample>& samples_)
{
	std::ifstream input_file(file_name);
	if (input_file.is_open()) {
		int width = 0;
		int height = 0;

		for (std::string str; std::getline(input_file, str) && str[0] == 'B'; )
		{
			std::vector<int> before{ stoi(str.substr(9,1)), stoi(str.substr(12,1)), stoi(str.substr(15,1)), stoi(str.substr(18,1)) };
			
			std::getline(input_file, str);
			std::istringstream iss (str);
			int a, b, c, d;
			iss >> a; iss >> b; iss >> c; iss >> d;
			std::vector<int> instr{ a, b, c, d };
			
			std::getline(input_file, str);
			std::vector<int> after{ stoi(str.substr(9,1)), stoi(str.substr(12,1)), stoi(str.substr(15,1)), stoi(str.substr(18,1)) };
			
			std::getline(input_file, str);

			samples_.push_back({ before, instr, after });
		}
	}
	else std::cout << "Error while opening input file!\n\n";
	input_file.close();
}

std::vector<int> addr(const std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {
	std::vector<int> result = regs;
	result[output] = regs[input_A] + regs[input_B];
	
	return result;
}
std::vector<int> addi(const std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {
	std::vector<int> result = regs;
	result[output] = regs[input_A] + input_B;

	return result;
}

std::vector<int> mulr(const std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {
	std::vector<int> result = regs;
	result[output] = regs[input_A] * regs[input_B];

	return result;
}
std::vector<int> muli(const std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {
	std::vector<int> result = regs;
	result[output] = regs[input_A] * input_B;

	return result;
}

std::vector<int> banr(const std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {
	std::vector<int> result = regs;
	result[output] = regs[input_A] & regs[input_B];

	return result;
}
std::vector<int> bani(const std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {
	std::vector<int> result = regs;
	result[output] = regs[input_A] & input_B;

	return result;
}

std::vector<int> borr(const std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {
	std::vector<int> result = regs;
	result[output] = regs[input_A] | regs[input_B];

	return result;
}
std::vector<int> bori(const std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {
	std::vector<int> result = regs;
	result[output] = regs[input_A] | input_B;

	return result;
}

std::vector<int> setr(const std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {
	std::vector<int> result = regs;
	result[output] = regs[input_A];

	return result;
}
std::vector<int> seti(const std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {
	std::vector<int> result = regs;
	result[output] = input_A;

	return result;
}

std::vector<int> gtir(const std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {
	std::vector<int> result = regs;
	
	if (input_A > regs[input_B]) result[output] = 1;
	else result[output] = 0;

	return result;
}
std::vector<int> gtri(const std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {
	std::vector<int> result = regs;
	
	if (regs[input_A] > input_B) result[output] = 1;
	else result[output] = 0;

	return result;
}
std::vector<int> gtrr(const std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {
	std::vector<int> result = regs;
	
	if (regs[input_A] > regs[input_B]) result[output] = 1;
	else result[output] = 0;

	return result;
}

std::vector<int> eqir(const std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {
	std::vector<int> result = regs;
	
	if (input_A == regs[input_B]) result[output] = 1;
	else result[output] = 0;

	return result;
}
std::vector<int> eqri(const std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {
	std::vector<int> result = regs;
	
	if (regs[input_A] == input_B) result[output] = 1;
	else result[output] = 0;

	return result;
}
std::vector<int> eqrr(const std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {
	std::vector<int> result = regs;
	
	if (regs[input_A] == regs[input_B]) result[output] = 1;
	else result[output] = 0;

	return result;
}