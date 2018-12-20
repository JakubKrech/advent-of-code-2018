#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <map>

#include <chrono>
#include <thread>

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

void get_input_from_file(std::string file_name, std::vector<std::pair<std::string, std::vector<int>>>&, int&);

int main()
{
	std::vector<std::pair<std::string, std::vector<int>>> data;
	int instruction_pointer_register;
	get_input_from_file("input.txt", data, instruction_pointer_register);

	std::vector<pfunc> functions_sorted_by_opcode{ bani, banr, muli, setr, bori, eqrr, gtir, mulr, gtrr, seti, gtri, eqri, addi, borr, eqir, addr };
	std::map<std::string, pfunc> functions_by_name{ { "bani",bani },{ "banr",banr },{ "muli",muli },{ "setr",setr },
													{ "bori",bori },{ "eqrr",eqrr },{ "gtir",gtir },{ "mulr",mulr },
													{ "gtrr",gtrr },{ "seti",seti },{ "gtri",gtri },{ "eqri",eqri },
													{ "addi",addi },{ "borr",borr },{ "eqir",eqir },{ "addr",addr } };

	std::vector<int> initial_data = { 0,0,0,0,0,0 };
	int instruction_pointer = 0;
	while (instruction_pointer < data.size()) {
		initial_data[instruction_pointer_register] = instruction_pointer;
		
		initial_data = functions_by_name[data[initial_data[instruction_pointer_register]].first](initial_data, 0, data[initial_data[instruction_pointer_register]].second[1],
			data[initial_data[instruction_pointer_register]].second[2], data[initial_data[instruction_pointer_register]].second[3]);

		instruction_pointer = initial_data[instruction_pointer_register];
		instruction_pointer++;
	}

	std::cout << initial_data[0] << " " << initial_data[1] << " " << initial_data[2] << " " << initial_data[3]
		<< " " << initial_data[4] << " " << initial_data[5] << "\n";

	system("pause");
	return 0;
}

void get_input_from_file(std::string file_name, std::vector<std::pair<std::string, std::vector<int>>>& data, int& instruction_pointer)
{
	std::ifstream input_file(file_name);
	if (input_file.is_open()) {

		std::string str;
		std::getline(input_file, str);
		instruction_pointer = stoi(str.substr(3, str.length() - 3));

		for (str; std::getline(input_file, str); )
		{
			std::string instruction_name = str.substr(0, 4);

			std::string numbers = str.substr(4, str.length() - 4);
			std::istringstream iss(numbers);

			int a, b, c;
			iss >> a; iss >> b; iss >> c;

			data.push_back(std::make_pair(instruction_name, std::vector<int>{ 0, a, b, c }));
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