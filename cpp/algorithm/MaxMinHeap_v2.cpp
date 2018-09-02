/*
* MaxMinHeap_v2.cpp
*
*  Created on: Dec 8, 2014
*      Author: mawang
*/


#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
class MinHeap
{
public:

	void push(const T t)
	{
		v_.push_back(t);
		std::push_heap(v_.begin(), v_.end(), std::greater<T>());
	}

	void pop()
	{
		std::pop_heap(v_.begin(), v_.end(), std::greater<T>());
		v_.pop_back();
	}

	T& top()
	{
		return v_.front();
	}

	bool empty()
	{
		return v_.empty();
	}

	unsigned int size()
	{
		return v_.size();
	}

private:
	std::vector<T>	v_;
};

template <typename T>
class MaxHeap
{
public:
	void push(const T t)
	{
		v_.push_back(t);
		std::push_heap(v_.begin(), v_.end(), std::less<T>());
	}

	void pop()
	{
		std::pop_heap(v_.begin(), v_.end(), std::less<T>());
		v_.pop_back();
	}

	T& top()
	{
		return v_.front();
	}

	bool empty()
	{
		return v_.empty();
	}

	unsigned int size() { return v_.size(); }

private:
	std::vector<T>	v_;
};

int main()
{
	MinHeap<int> minHeap;
	MaxHeap<int> maxHeap;

	minHeap.push(10);
	minHeap.push(5);
	minHeap.push(12);
	minHeap.push(3);
	minHeap.push(4);

	maxHeap.push(10);
	maxHeap.push(5);
	maxHeap.push(12);
	maxHeap.push(3);
	maxHeap.push(4);

	while ( !minHeap.empty()) {
		std::cout << minHeap.top() << " ";
		minHeap.pop();
	}
	std::cout << std::endl;

	while ( !maxHeap.empty()) {
		std::cout << maxHeap.top() << " ";
		maxHeap.pop();
	}
	std::cout << std::endl;
}
