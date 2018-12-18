#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

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

void get_input_from_file(std::string file_name, std::vector<Sample>& samples_, std::vector<std::vector<int>>&);

int main()
{
	std::vector<Sample> samples_;
	std::vector<std::vector<int>> test_data;
	get_input_from_file("input.txt", samples_, test_data);
	
	std::vector<pfunc> functions{ addr ,addi , mulr, muli, banr, bani, borr, bori, setr, seti, gtir, gtri, gtrr, eqir, eqri, eqrr };


	std::cout << "SAMPLES SIZE: " << samples_.size() << "\n";

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
	std::cout << "Samples behaving like 3 or more opcodes: " << samples_behaving_correctly << "\n\n";


	std::cout << "     ";
	for (int i = 0; i < 16; i++) {
		std::cout << std::setw(2) << i << " ";
	}
	std::cout << "\n";

	for (int z = 0; z < functions.size(); z++) {
		std::vector<int> counters(16, 0);
		for (auto x : samples_) {
			std::vector<int> result = functions[z](x.before, x.instruction[0], x.instruction[1], x.instruction[2], x.instruction[3]);

			if (result[0] == x.after[0] && result[1] == x.after[1] && result[2] == x.after[2] && result[3] == x.after[3])
				counters[x.instruction[0]]++;
		}

		int function_id = -1;
		std::cout << "#" << std::setw(2) << z << "  ";
		for (auto c : counters) {
			std::cout << std::setw(2) << c << " ";
		}
		std::cout << "\n";
	}

	// Printing results for every function reveals some sort of puzzle.
	// We can always know opcode for one of them, and after we discard known function from our puzzle
	// we are able to get info about next function's opcode.
	// You can find related screenshot in git files, results:
	// addr - 15, addi - 12, mulr - 7, muli - 2, banr - 1, bani - 0, borr - 13, bori - 4
	// setr - 3, seti - 9, gtir - 6, gtri - 10, gtrr - 8, eqir - 14, eqri - 11, eqrr - 5
	// Function for calculating it could be made, but for now i decided to solve it by hand.

	std::vector<pfunc> functions_sorted_by_opcode{ bani, banr, muli, setr, bori, eqrr, gtir, mulr, gtrr, seti, gtri, eqri, addi, borr, eqir, addr };

	std::vector<int> input_test_data = { 0,0,0,0 };
	for (int i = 0; i < test_data.size(); i++)
	{
		input_test_data = functions_sorted_by_opcode[test_data[i][0]](input_test_data, test_data[i][0], test_data[i][1], test_data[i][2], test_data[i][3]);
	}

	std::cout << "\nTEST RESULT: >>" << input_test_data[0] << "<< " << input_test_data[1] << " " << input_test_data[2] << " " << input_test_data[3] << "\n\n";

	system("pause");
	return 0;
}

void get_input_from_file(std::string file_name, std::vector<Sample>& samples_, std::vector<std::vector<int>>& test_data)
{
	std::ifstream input_file(file_name);
	if (input_file.is_open()) {

		std::string str;
		for (str; std::getline(input_file, str) && str[0] == 'B'; )
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

		std::getline(input_file, str);

		for (str; std::getline(input_file, str); )
		{
			std::istringstream iss(str);

			int a, b, c, d;
			iss >> a; iss >> b; iss >> c; iss >> d;

			std::vector<int> data{ a, b, c, d };

			test_data.push_back(data);
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