#pragma once

#include <list>
#include <mutex>
#include <algorithm>
#include <iostream>


class Protected_List
{
public:
	void add_to_list();
	bool list_contains(int value_to_find);
	void print();
private:
	std::list<int> some_list;
	std::mutex some_mutex;
};

void Protected_List::add_to_list()
{
	std::lock_guard<std::mutex> guard(some_mutex);
	for (int i = 0; i < 100; ++i)
		some_list.push_back(i);
}

bool Protected_List::list_contains(int value_to_find)
{
	auto p = std::find(some_list.begin(), some_list.end(), value_to_find);
	if (p == some_list.end())
		return false;
	return true;
}

void Protected_List::print()
{
	for (auto p:some_list)
	{
		std::cout << p << " ";
	}
	std::cout << std::endl;
}