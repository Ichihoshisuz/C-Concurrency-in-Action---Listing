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

// ��Ӧ����ôд������� dangling reference �������ܻ��ظ������Ѿ����ٵı�����
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