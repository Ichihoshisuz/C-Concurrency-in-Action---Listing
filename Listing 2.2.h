#pragma once

#include <stdexcept>
#include "Listing 2.1.h"

void do_something_in_current_thread()
{
	return;
}

void f()
{
	int some_local_state = 0;
	func m(some_local_state);
	std::thread t(m);
	try
	{
		do_something_in_current_thread(); // 什么也没干，用于演示。
	}
	catch (std::runtime_error) // 也是没有意义的
	{
		t.join();
		throw;
	}
	t.join();
}