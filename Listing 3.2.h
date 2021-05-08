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

// ���￪ʼͨ��ָ�뽫�� mutex �����ı������ݳ�ȥ

some_data* unprotected; // ��һ��ȫ�ֱ�������ܱ���������

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