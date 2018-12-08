#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<int> get_input_from_file(std::string);

int calculate_sum_of_metadata_entries(const std::vector<int>&);
int calculate_node_metadata_value(const std::vector<int>&, int&);

int calculate_root_node_value(const std::vector<int>&);
int calculate_node_value(const std::vector<int>&, int&);

int main()
{
	std::vector<int> data = std::move(get_input_from_file("input.txt"));

	std::cout << "Part One: " << calculate_sum_of_metadata_entries(data) << "\n";

	std::cout << "Part Two: " << calculate_root_node_value(data) << "\n\n";

	system("pause");
	return 0;
}

int calculate_sum_of_metadata_entries(const std::vector<int>& data)
{
	int sum_of_metadata_entries = 0;

	for (int i = 0; i < data.size(); i++) {
		sum_of_metadata_entries += calculate_node_metadata_value(data, i);
	}
	return sum_of_metadata_entries;
}

int calculate_node_metadata_value(const std::vector<int>& data, int& i)
{
	int node_metadata_value = 0;

	int child_nodes_quantity = data[i];
	int metadata_entries_quantity = data[++i];
	
	for (int j = 0; j < child_nodes_quantity; j++) {
		node_metadata_value += calculate_node_metadata_value(data, ++i);
	}

	for (int k = 0; k < metadata_entries_quantity; k++) {
		node_metadata_value += data[++i];
	}
	return node_metadata_value;
}

int calculate_root_node_value(const std::vector<int>& data)
{
	int root_node_value = 0;

	for (int i = 0; i < data.size(); i++) {
		root_node_value += calculate_node_value(data, i);
	}
	return root_node_value;
}

int calculate_node_value(const std::vector<int>& data, int& i)
{
	int node_value = 0;

	int child_nodes_quantity = data[i];
	int metadata_entries_quantity = data[++i];

	if (child_nodes_quantity > 0) {
		std::vector<int> temp_values;
		for (int j = 0; j < child_nodes_quantity; j++) {
			temp_values.push_back(calculate_node_value(data, ++i));
		}

		for (int k = 0; k < metadata_entries_quantity; k++) {
			if (temp_values.size() > (data[++i] - 1)) {
				node_value += temp_values[(data[i] - 1)];
			}
		}
	}
	else {
		for (int k = 0; k < metadata_entries_quantity; k++) {
			node_value += data[++i];
		}
	}
	return node_value;
}

std::vector<int> get_input_from_file(std::string file_name)
{
	std::vector<int> data;

	std::ifstream input_file(file_name);
	if (input_file.is_open()) {
		int temp;
		while (input_file >> temp) {
			data.push_back(temp);
		}
	}
	else std::cout << "Error while opening input file!\n\n";
	input_file.close();

	return data;
}
