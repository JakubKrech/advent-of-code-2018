#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>

struct Pot
{
	int id;
	bool contain_plant;
};

struct Combination
{
	std::vector<int> comb;
	bool contain_plant;
};

void get_input_from_file(std::string, std::list<Pot>&, std::vector<Combination>&);

void produce_next_pots_generations(std::list<Pot>&, const std::vector<Combination>&, long long, int&);

int main()
{
	std::list<Pot> pots_;
	std::vector<Combination> combinations_;
	get_input_from_file("input.txt", pots_, combinations_);

	int previous_counter = 0;
	produce_next_pots_generations(pots_, combinations_, 2000, previous_counter);
	// optimizing this algorithm for 50000000000 would be hard task, luckily after analyzing some inputs
	// it becomes clear that there is a pattern after certain number or generations difference in results
	// for every next generation becomes constant and equals (for my input data) 88
	// using that knowledge we can calculate final result by multiplying number of remaining generations by 88

	std::cout << "\n\n";
	for (auto x : pots_) {
		std::cout << x.contain_plant;
	}
	std::cout << "\n";

	// for part 2:
	// result for 2000th iteration = 176304, diff = 88
	long long result = 176304 + ((50000000000 - 2000) * 88);

	std::cout << "\nRESULT PART 2: " << result << "\n\n";

	system("pause");
	return 0;
}

void produce_next_pots_generations(std::list<Pot>& pots_, const std::vector<Combination>& combinations_, 
	long long generations, int& previous_counter)
{
	for (long long i = 1; i <= generations; i++) {
		while (pots_.begin()->contain_plant == true ||
			std::next(pots_.begin(), 1)->contain_plant == true) {

			pots_.push_front({ pots_.begin()->id - 1, false });
		}

		while (std::prev(pots_.end(), 1)->contain_plant == true ||
			std::prev(pots_.end(), 2)->contain_plant == true ||
			std::prev(pots_.end(), 3)->contain_plant == true) {

			pots_.push_back({ std::prev(pots_.end(), 1)->id + 1, false });
		}

		if (pots_.begin()->contain_plant == false &&
			std::next(pots_.begin(), 1)->contain_plant == false &&
			std::next(pots_.begin(), 2)->contain_plant == false &&
			std::next(pots_.begin(), 3)->contain_plant == false) pots_.pop_front();

		if (std::prev(pots_.end(), 1)->contain_plant == false &&
			std::prev(pots_.end(), 2)->contain_plant == false &&
			std::prev(pots_.end(), 3)->contain_plant == false &&
			std::prev(pots_.end(), 4)->contain_plant == false) pots_.pop_back();

		std::list<Pot> new_generation = pots_;

		std::list<Pot>::iterator pots_iterator = std::next(pots_.begin(), 2);
		std::list<Pot>::iterator new_gen_iterator = std::next(new_generation.begin(), 2);

		for (; pots_iterator != std::prev(pots_.end(), 2); pots_iterator++, new_gen_iterator++) {
			for (auto x : combinations_) {

				if (std::prev(pots_iterator, 2)->contain_plant == x.comb[0] &&
					std::prev(pots_iterator, 1)->contain_plant == x.comb[1] &&
					pots_iterator->contain_plant == x.comb[2] &&
					std::next(pots_iterator, 1)->contain_plant == x.comb[3] &&
					std::next(pots_iterator, 2)->contain_plant == x.comb[4])
				{
					new_gen_iterator->contain_plant = x.contain_plant;
				}
			}
		}
		pots_ = std::move(new_generation);

		long long id_sum_of_plant_cont_pots = 0;
		for (auto x : pots_)
			if (x.contain_plant == 1) id_sum_of_plant_cont_pots += x.id;

		std::cout << "#" << i << " Sum: " << id_sum_of_plant_cont_pots << "  diff: " 
			<< id_sum_of_plant_cont_pots - previous_counter << "\n";
		previous_counter = id_sum_of_plant_cont_pots;
	}
}

void get_input_from_file(std::string file_name, std::list<Pot>& pots_, std::vector<Combination>& combinations_)
{
	std::ifstream input_file(file_name);
	if (input_file.is_open()) {
		std::string initial_state_line;
		std::getline(input_file, initial_state_line);
		std::string initial_state = initial_state_line.substr(initial_state_line.find(":") + 2,
			initial_state_line.length() - initial_state_line.find(":") + 2);
		std::cout << initial_state << "\n";
		
		for (int i = 0; i < initial_state.length(); i++) {
			if (initial_state[i] == '#')
				pots_.insert(pots_.end(), { i, true });
			else
				pots_.insert(pots_.end(), { i, false });
		}

		for (std::string str; std::getline(input_file, str); )
		{
			if (str.length() > 0) {
				std::string comb = str.substr(0, 5);
				
				std::vector<int> comb_vector;

				for (int i = 0; i < comb.length(); i++) {
					if (comb[i] == '#') comb_vector.push_back(1);
					else comb_vector.push_back(0);
				}

				bool result;
				if (str.substr(str.find('>') + 2, 1) == "#")
					result = 1;
				else
					result = 0;

				combinations_.push_back({ comb_vector, result });
			}
		}
	}
	else std::cout << "Error while opening input file!\n\n";
	input_file.close();
}