/*
* encapsulated from https://codeconnect.wordpress.com/2013/09/05/max-min-heap-using-c-stl/
*/
#include <iostream>
#include <queue>
#include <functional>

template <typename T>
class MinHeap
{
public:
	void push(const T t) { minHeap_.push(t);}
	void pop() { minHeap_.pop();}
	T top() { return minHeap_.top(); }
	bool empty() { return minHeap_.empty(); }
	unsigned int size() { return minHeap_.size(); }

private:
	std::priority_queue<T, std::vector<T>, std::greater<T> > minHeap_;
};

template <typename T>
class MaxHeap
{
public:
	void push(const T t) { maxHeap_.push(t);}
	void pop() { maxHeap_.pop();}
	T top() { return maxHeap_.top(); }
	bool empty() { return maxHeap_.empty(); }
	unsigned int size() { return maxHeap_.size(); }

private:
	std::priority_queue<T, std::vector<T>, std::less<T> > maxHeap_;
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
