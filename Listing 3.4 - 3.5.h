#pragma once

// Listing 3.4 An outline class definitoin for a thread-safe stack

#include <exception>
#include <memory>
#include <mutex>
#include <stack>

struct empty_stack :public std::runtime_error
{
	// ≥¢ ‘
	// const char* what() const noexcept;
	explicit empty_stack(const char* s) :std::runtime_error(s) {}
};

template<typename T>
class threadsafe_stack
{
public:
	threadsafe_stack() {}
	threadsafe_stack(const threadsafe_stack& other);
	threadsafe_stack& operator=(const threadsafe_stack&) = delete;

	bool empty() const;
	void push(T& new_value);
	void pop(T& value);
	std::shared_ptr<T> pop();

private:
	std::stack<T> data;
	mutable std::mutex m;
};

// Listing 3.5 A fleshed-out class defintion for a thread-safe stack

template<typename T>
threadsafe_stack<T>::threadsafe_stack(const threadsafe_stack& other)
{
	std::lock_guard<std::mutex> lock(other.m);
	data = other.data;
}

template<typename T>
bool threadsafe_stack<T>::empty() const
{
	std::lock_guard<std::mutex> lock(m);
	return data.empty();
}

template <typename T>
void threadsafe_stack<T>::push(T& new_val)
{
	std::lock_guard<std::mutex> lock(m);
	data.push(std::move(new_val)); 
}

template <typename T>
std::shared_ptr<T> threadsafe_stack<T>::pop()
{
	std::lock_guard<std::mutex> lock(m);
	if (data.empty())
		throw empty_stack("Stack is empty.");
	std::shared_ptr<T> const temp(std::make_shared<T>(data.top()));
	data.pop();
	return temp;
}

template <typename T>
void threadsafe_stack<T>::pop(T& value)
{
	std::lock_guard<std::mutex> lock(m);
	if (data.empty())
		throw empty_stack("Stack is empty.");
	value = data.top();
	data.pop();
}