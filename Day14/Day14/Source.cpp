#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void iterate_current_recipe(std::vector<int>, int&);

int main()
{
	int input = 880751;
	
	std::vector<int> recipes{ 3,7 };

	int current_recipe_A = 0;
	int current_recipe_B = 1;

	std::string score_of_ten_recipes;

	for (int i = 0; i < input + 8;) {

		int new_recipe_sum = recipes[current_recipe_A] + recipes[current_recipe_B];
		
		if (new_recipe_sum >= 10) {
			int tens = new_recipe_sum / 10;
			int unit = new_recipe_sum % 10;

			recipes.push_back(tens);
			recipes.push_back(unit);

			iterate_current_recipe(recipes, current_recipe_A);
			iterate_current_recipe(recipes, current_recipe_B);

			if (i >= input - 2) {
				score_of_ten_recipes += std::to_string(tens);
				score_of_ten_recipes += std::to_string(unit);
			}
			i += 2;
		}
		else
		{
			recipes.push_back(new_recipe_sum);

			iterate_current_recipe(recipes, current_recipe_A);
			iterate_current_recipe(recipes, current_recipe_B);

			if (i >= input - 2)
				score_of_ten_recipes += std::to_string(new_recipe_sum);

			i++;
		}
	}
	std::cout << "Score of ten recipes = " << score_of_ten_recipes << "\n";

	std::string current_sequence = "37";
	std::string input_string = std::to_string(input);
	std::cout << input << "   " << input_string << "\n\n";

	for (int i = 2; i < recipes.size(); i++)
	{
		current_sequence += std::to_string(recipes[i]);
		if (current_sequence.length() > input_string.length())
			current_sequence.erase(0, 1);

		std::cout << current_sequence << " " << input_string << "\n";

		if (current_sequence == input_string) {
			std::cout << "Ammount of recipes = " << i - input_string.length() + 1 << "\n";
			break;
		}
	}

	

	system("pause");
	return 0;
}

void iterate_current_recipe(std::vector<int> recipes, int& x)
{
	/*int iterations = recipes[x] + 1;
	
	for (int i = 0; i < iterations; i++)
	{
		x++;
		if (x > (recipes.size() - 1)) x = 0;
	}*/

	x += recipes[x];
	while (x >= recipes.size()) 
		x -= recipes.size();
}