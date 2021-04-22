#pragma once

#include <thread>

class func
{
public:
	func(int& i) :N(i) {}
	void operator()();
	void do_something(int& i) { ++i; };
private:
	int& N;
};

// 不应该这么写。会出现 dangling reference ，即可能会重复访问已经销毁的变量。
void func::operator()()
{
	for (unsigned j = 0; j < 100000000; ++j)
	{
		do_something(N);
	}
}

void oops()
{
	int some_local_state = 0;
	func m(some_local_state);
	std::thread m_thread(m);
	m_thread.detach();
}