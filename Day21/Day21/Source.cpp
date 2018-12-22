#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
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

std::vector<int> results; // ugly global vector, i know it

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

	std::vector<int> initial_data = { 0,0,0,0,0,0 };

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

	// This solution is a result of checking what given input really does to the code.
	// It writes out all values of register[0] that would stop algorithm. Essentially only function eqrr was modified.
	// Solution is not optimized at all, brute forcing through all possible algorithm-stopping-values and
	// finding values that execute lowest and highest ammount of instructions takes around 97s for Part 2.
	// Also i use ugly global vector to store those values, so ammount of code that
	// i have to modify from Day19 code is minimal.

	std::cout << "Part 1: " << results[0] <<
		"\nPart 2: " << results[results.size() - 1] << "\n";

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

void mulr(std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {
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
/*void eqrr(std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {
	if (regs[input_A] == regs[input_B]) regs[output] = 1;
	else regs[output] = 0;
}*/
void eqrr(std::vector<int>& regs, int opcode, int input_A, int input_B, int output) {

	bool already_added = false;

	for (auto x : results)
		if (x == regs[input_A]) {
			already_added = true;
			break;
		}

	if (already_added == false) {
		results.push_back(regs[input_A]);
	}
	
	if (already_added == true) regs[output] = 1;
	else {
		if (regs[input_A] == regs[input_B]) regs[output] = 1;
		else regs[output] = 0;
	}
}
