// Listing 3.2 Accidentally passing out a reference to protected data

#pragma once

#include <string>
#include <mutex>

class some_data
{
public:
	void do_something() {};
private:
	int a;
	std::string str;
};

class data_wrapper
{
public:
	template<typename Function>
	void process_data(Function func)
	{
		std::lock_guard<std::mutex> lg(m);
		func(data);
	}
private:
	some_data data;
	std::mutex m;
};

// 这里开始通过指针将由 mutex 保护的变量传递出去

some_data* unprotected; // 用一个全局变量获得受保护的数据

void malicious_function(some_data& protected_data)
{
	unprotected = &protected_data;
}

data_wrapper x;

void foo()
{
	x.process_data(malicious_function);
	unprotected->do_something();
}