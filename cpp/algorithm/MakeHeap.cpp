/*
* MakeHeap.cpp
*
*  Created on: Dec 4, 2014
*      Author: mawang
*/
#include <iostream>
#include <algorithm> //std::make_heap, std::pop_heap, std::push_heap, std::sort_heap
#include <vector>

using namespace std;


int main()
{
	int myints[] = {10,20,30,5,15};
	vector<int> v(myints, myints+5);

	make_heap(v.begin(), v.end());
	cout << "initial max heap: " << v.front() << endl;

	pop_heap(v.begin(), v.end());
	v.pop_back();
	cout << "max heap after pop: " << v.front() << endl;

	v.push_back(99);
	push_heap(v.begin(), v.end());
	cout << "max heap after push: " << v.front() << endl;

	sort_heap(v.begin(), v.end());
	cout << "final sorted range: ";
	for (auto item : v) {
		cout << ' ' << item;
	}
	cout << endl;
	return 0;
}

