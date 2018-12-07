#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>  

struct Step
{
	int id;
	int time_left_to_complete = id + 61;
	std::vector<char> requirements;
	bool finished = false;
	bool completion_in_progress = false;
};

void get_input_from_file(std::string, std::vector<Step>&);
std::string find_order_of_steps(std::vector<Step>);
int find_time_needed_to_complete_all_steps(std::vector<Step>);


int main()
{
	std::vector<Step> steps_;
	for (int i = 0; i < 91 - 65; i++) steps_.push_back(Step{ i });
	get_input_from_file("input.txt", steps_);
	for (auto x : steps_) std::sort(x.requirements.begin(), x.requirements.end());

	std::cout << "Part One: " << find_order_of_steps(steps_) << "\n";

	std::cout << "Part Two: " << find_time_needed_to_complete_all_steps(steps_) << " seconds\n\n";

	system("pause");
	return 0;
}

std::string find_order_of_steps(std::vector<Step> steps_)
{
	std::string order;
	int steps_completed = 0;

	while (steps_completed != steps_.size()) {
		for (int i = 0; i < steps_.size(); i++) {
			if (steps_[i].finished == false) {
				bool all_requirements_fullfilled = true;

				for (auto j : steps_[i].requirements) {
					if (steps_[j - 65].finished == false) {
						all_requirements_fullfilled = false;
						break;
					}
				}

				if (all_requirements_fullfilled) {
					steps_[i].finished = true;
					order += char(i + 65);
					steps_completed++;
					i = 0;
				}
			}
		}
	}

	return order;
}

int find_time_needed_to_complete_all_steps(std::vector<Step> steps_)
{
	int free_workers = 5;
	int steps_completed = 0;
	int total_seconds = 0;

	while (steps_completed != steps_.size()) {
		for (int i = 0; i < steps_.size(); i++) {
			if (steps_[i].finished == false && steps_[i].completion_in_progress == false && free_workers > 0) {
				bool all_requirements_fullfilled = true;

				for (auto j : steps_[i].requirements) {
					if (steps_[j - 65].finished == false) {
						all_requirements_fullfilled = false;
						break;
					}
				}

				if (all_requirements_fullfilled) {
					steps_[i].completion_in_progress = true;
					free_workers--;
				}
			}
		}

		for (auto &x : steps_) {
			if (x.completion_in_progress && --x.time_left_to_complete == 0) {
				x.completion_in_progress = false;
				x.finished = true;
				free_workers++;
				steps_completed++;
			}
		}
		total_seconds++;
	}
	return total_seconds;
}

void get_input_from_file(std::string file_name, std::vector<Step>& target_object)
{
	std::ifstream input_file(file_name);
	if (input_file.is_open()) {
		for (std::string str; std::getline(input_file, str); )
		{
			target_object[str[36] - 65].requirements.push_back(str[5]);
		}
	}
	else std::cout << "Error while opening input file!\n\n";
	input_file.close();
}