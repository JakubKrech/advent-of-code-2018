#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <map>

typedef void func(std::vector<int>&, int, int, int, int);
typedef func* pfunc;

void addr(std::vector<int>&, int, int, int, int);
void addi(std::vector<int>&, int, int, int, int);

void mulr(std::vector<int>&, int, int, int, int);
void muli(std::vector<int>&, int, int, int, int);

void banr(std::vector<int>&, int, int, int, int);
void bani(std::vector<int>&, int, int, int, int);

void borr(std::vector<int>&, int, int, int, int);
void bori(std::vector<int>&, int, int, int, int);

void setr(std::vector<int>&, int, int, int, int);
void seti(std::vector<int>&, int, int, int, int);

void gtir(std::vector<int>&, int, int, int, int);
void gtri(std::vector<int>&, int, int, int, int);
void gtrr(std::vector<int>&, int, int, int, int);

void eqir(std::vector<int>&, int, int, int, int);
void eqri(std::vector<int>&, int, int, int, int);
void eqrr(std::vector<int>&, int, int, int, int);

void get_input_from_file(std::string file_name, std::vector<std::pair<std::string, std::vector<int>>>&, int&);

int main()
{
	std::vector<std::pair<std::string, std::vector<int>>> data;
	int instruction_pointer_register;
	get_input_from_file("input.txt", data, instruction_pointer_register);

	std::vector<pfunc> functions_sorted_by_opcode{ bani, banr, muli, setr, bori, eqrr, gtir, mulr,
		gtrr, seti, gtri, eqri, addi, borr, eqir, addr };
	std::map<std::string, pfunc> functions_by_name{
		{ "bani",bani },{ "banr",banr },{ "muli",muli },{ "setr",setr },
		{ "bori",bori },{ "eqrr",eqrr },{ "gtir",gtir },{ "mulr",mulr },
		{ "gtrr",gtrr },{ "seti",seti },{ "gtri",gtri },{ "eqri",eqri },
		{ "addi",addi },{ "borr",borr },{ "eqir",eqir },{ "addr",addr } };

	std::vector<int> initial_data = { 0,0,0,0,0,0 }; // Part 1
	//std::vector<int> initial_data = { 1,0,0,0,0,0 }; // Part 2
	int instruction_pointer = 0;
	while (instruction_pointer < data.size()) {
		initial_data[instruction_pointer_register] = instruction_pointer;
		
		functions_by_name[data[initial_data[instruction_pointer_register]].first](
			initial_data, 0, data[initial_data[instruction_pointer_register]].second[1],
			data[initial_data[instruction_pointer_register]].second[2],
			data[initial_data[instruction_pointer_register]].second[3]);

		instruction_pointer = initial_data[instruction_pointer_register];
		
		instruction_pointer++;
	}

	std::cout << "Part 1:  Registers values: " << initial_data[0] << " " << initial_data[1] <<
		" " << initial_data[2] << " " << initial_data[3] << 
		" " << initial_data[4] << " " << initial_data[5] << "\n\n";
	std::cout << "Part 1:  Register[0] = " << initial_data[0] << "\n\n";

	// Part Two would require 10551320*10551320 iterations of registers 2-10 to solve the puzzle
	// with previous approach. It's a little too much work, so after some additional examination,
	// i came up with shorter solution. It cuts most of iterations that would not affect the final result.

	int r0 = 0;
	int r1;
	for (int r4 = 0; r4 <= 10551319; r4++)
	{
		for (int r5 = 0; r5 <= 10551319; r5++)
		{
			if (r4*r5 == 10551319) r0 += r4;
			else if (r4*r5 > 10551319) break;
		}
	}

	std::cout << "Part 2:  Register[0] = " << r0 << "\n\n";

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

void addr(std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {
	regs[output] = regs[input_A] + regs[input_B];
}
void addi(std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {
	regs[output] = regs[input_A] + input_B;
}

void mulr( std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {
	regs[output] = regs[input_A] * regs[input_B];
}
void muli(std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {
	regs[output] = regs[input_A] * input_B;
}

void banr(std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {
	regs[output] = regs[input_A] & regs[input_B];
}
void bani(std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {
	regs[output] = regs[input_A] & input_B;
}

void borr(std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {
	regs[output] = regs[input_A] | regs[input_B];
}
void bori(std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {
	regs[output] = regs[input_A] | input_B;
}

void setr(std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {
	regs[output] = regs[input_A];
}
void seti(std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {
	regs[output] = input_A;
}

void gtir(std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {
	if (input_A > regs[input_B]) regs[output] = 1;
	else regs[output] = 0;
}
void gtri(std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {
	if (regs[input_A] > input_B) regs[output] = 1;
	else regs[output] = 0;
}
void gtrr(std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {
	if (regs[input_A] > regs[input_B]) regs[output] = 1;
	else regs[output] = 0;
}

void eqir(std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {
	if (input_A == regs[input_B]) regs[output] = 1;
	else regs[output] = 0;
}
void eqri(std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {
	if (regs[input_A] == input_B) regs[output] = 1;
	else regs[output] = 0;
}
void eqrr(std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {
	if (regs[input_A] == regs[input_B]) regs[output] = 1;
	else regs[output] = 0;
}