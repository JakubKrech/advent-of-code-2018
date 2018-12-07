#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Event
{
	int year, month, day;
	int hour, minute;
	std::string action;
};

struct Guard
{
	int id;
	std::vector<int> minute_portions;
	int total_time_asleep;

	void operator+=(const Guard& g)
	{
		total_time_asleep += g.total_time_asleep;
		for (int i = 0; i < minute_portions.size(); i++)
		{
			minute_portions[i] += g.minute_portions[i];
		}
	}
};

void print_events(const std::vector<Event>&);

int main()
{
	std::vector<Event> events_;
	std::vector<Guard> guards_;

	std::ifstream input_file("input.txt");
	if (input_file.is_open()) {
		for (std::string str; std::getline(input_file, str); )
		{
			std::string date_and_time = str.substr(1, 16);

			Event new_event{
				std::stoi(date_and_time.substr(0,4)),
				std::stoi(date_and_time.substr(5,2)),
				std::stoi(date_and_time.substr(8,2)),
				std::stoi(date_and_time.substr(11,2)),
				std::stoi(date_and_time.substr(14,2)),
				str.substr(str.find("]") + 2, 25)
			};

			for (std::vector<Event>::iterator i = events_.begin(); i <= events_.end(); i++)
			{
				if (i == events_.end() ||
					new_event.month <  i->month  ||
					new_event.month == i->month  &&  new_event.day <  i->day  ||
					new_event.month == i->month  &&  new_event.day == i->day  &&  new_event.hour  < i->hour  ||
					new_event.month == i->month  &&  new_event.day == i->day  &&  new_event.hour == i->hour  &&  new_event.minute < i->minute)
				{
					events_.insert(i, new_event);
					break;
				}
			}
		}
	}
	input_file.close();

	//print_events(events_);

	for (int i = 0; i < events_.size(); i++)
	{
		if (events_[i].action.substr(0, 1) == "G")
		{
			int total_time_asleep = 0;
			std::vector<int> minute_portions;
			minute_portions.resize(60, 0);

			int j = i;

			while ((j + 1) < events_.size() && events_[j + 1].action.substr(0, 1) == "f" &&
				   (j + 2) < events_.size() && events_[j + 2].action.substr(0, 1) == "w") 
			{
				total_time_asleep += events_[j + 2].minute - events_[j + 1].minute;

				for (int k = events_[j + 1].minute; k < events_[j + 2].minute; k++)
					minute_portions[k]++;

				j += 2;
			}

			int key = stoi(events_[i].action.substr(events_[i].action.find("#") + 1,
				events_[i].action.find("b") - 2 - events_[i].action.find("#")));
			bool found = false;

			if (guards_.size() == 0) guards_.push_back(Guard{ key, minute_portions, total_time_asleep });
			else {
				for (int l = 0; l < guards_.size(); l++) {
					if (guards_[l].id == key) {
						guards_[l] += Guard{ key,minute_portions, total_time_asleep };
						found = true;
					}
				}
				if (found == false)
					guards_.push_back(Guard{ key, minute_portions, total_time_asleep });
			}
		}
	}
	

	Guard guard_sleeping_most = guards_[0];

	for (auto x : guards_) {
		if (x.total_time_asleep > guard_sleeping_most.total_time_asleep) guard_sleeping_most = x;
	}
	
	int minute_slept_most = 0;
	
	for (int i = 0; i < guard_sleeping_most.minute_portions.size(); i++)
		if (guard_sleeping_most.minute_portions[i] > guard_sleeping_most.minute_portions[minute_slept_most])
			minute_slept_most = i;
			
	std::cout << "Guard #" << guard_sleeping_most.id << " spent the most minutes asleep, mostly at minute 00:";
	(minute_slept_most > 9) ? (std::cout << minute_slept_most) : (std::cout << "0" << minute_slept_most);
	
	std::cout << "\nPart One: " << guard_sleeping_most.id * minute_slept_most << "\n";
	

	Guard guard_same_minute = guards_[0];	// guard most frequently asleep on the same minute
	int same_minute_index = 0;				// minute in which the guard was asleep
	
	for (const auto &x : guards_) {
		for (int i = 0; i < x.minute_portions.size(); i++) {
			if (x.minute_portions[i] > guard_same_minute.minute_portions[same_minute_index]) {
				guard_same_minute = x;
				same_minute_index = i;
			}
		}
	}

	std::cout << "\nGuard #" << guard_same_minute.id << " was most frequently asleep on the same minute, it was minute 00:";
	(same_minute_index > 9) ? (std::cout << same_minute_index << "\n") : (std::cout << "0" << same_minute_index << "\n");
	std::cout << "Part Two: " << guard_same_minute.id * same_minute_index << "\n\n";

	system("pause");
	return 0;
}

void print_events(const std::vector<Event>& events_)
{
	for (auto x : events_) {
		std::cout << "[" << x.year << "-";
		(x.month > 9) ? (std::cout << x.month << "-") : (std::cout << "0" << x.month << "-");
		(x.day > 9) ? (std::cout << x.day << " ") : (std::cout << "0" << x.day << " ");
		(x.hour > 9) ? (std::cout << x.hour << ":") : (std::cout << "0" << x.hour << ":");
		(x.minute > 9) ? (std::cout << x.minute << "] ") : (std::cout << "0" << x.minute << "] ");
		std::cout << x.action << "\n";
	}
}