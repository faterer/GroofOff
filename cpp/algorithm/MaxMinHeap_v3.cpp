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
		push_heap(0, v_.size()-1, 0, v_.back());
	}

	void pop()
	{
		adjust_heap(0, 0, v_.size(), v_.back());
		for (auto i : v_)
			std::cout << i << " ";
		std::cout << "---" <<std::endl;
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

	void print()
	{
		for (auto i : v_)
			std::cout << i << " ";
		std::cout << std::endl;
	}

private:
	std::vector<T>	v_;
	void push_heap(unsigned int first,
				   unsigned int holeIndex,
				   unsigned int topIndex,
				   T value)
	{
		unsigned int parent = (holeIndex - 1)/2;
		while (holeIndex > topIndex && v_[first + parent] > value) {
			v_[first + holeIndex] = v_[first + parent];
			holeIndex = parent;
			parent = (holeIndex - 1)/2;
		}
		v_[first+holeIndex] = value;
	}

	void adjust_heap(unsigned int first,
					 unsigned int holeIndex,
					 unsigned int len,
					 T value)
	{
		unsigned int topIndex = holeIndex;
	    unsigned int secondChild = holeIndex;
	    while (secondChild < (len - 1) / 2)
		{
	    	secondChild = 2 * (secondChild + 1);
	    	if (v_[first + secondChild] > v_[first + (secondChild - 1)])
	    		secondChild--;

	    	v_[first + holeIndex] = v_[first + secondChild];
	    	holeIndex = secondChild;
		}

	    if ((len & 1) == 0 && secondChild == (len - 2) / 2)
		{
	    	secondChild = 2 * (secondChild + 1);
	    	v_[first + holeIndex] = v_[first + (secondChild - 1)];
	    	holeIndex = secondChild - 1;
		}

	    push_heap(first, holeIndex, topIndex, value);
	}
};


int main()
{
	MinHeap<int> minHeap;

	minHeap.push(10);
	minHeap.push(5);
	minHeap.push(12);
	minHeap.push(3);
	minHeap.push(4);
	minHeap.push(8);
	minHeap.print();

	//minHeap.pop();
	while ( !minHeap.empty()) {

		//std::cout << minHeap.top() << " ";
		minHeap.pop();
		minHeap.print();
	}
	std::cout << std::endl;

}
