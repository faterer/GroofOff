#include <iostream>
#include <functional>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;
/*
mem_fn returns a function object to a member function of an object,
which can then be called like a regular function.
*/

int main() {
	vector<string> words{"The", "quick", "brown", "fox"};
	
	vector<size_t> lengths;
	//for each word in words, from begin() to end(),
	//append to the vector lengths the length of each word
	transform(words.begin(), words.end(), back_inserter(lengths), mem_fn(&string::size));
	
	for (auto n : lengths)
		cout << n << " ";
	cout << "\n\n";
	
	lengths.clear();
	//transform using lambda experssion
	transform(words.begin(), words.end(), back_inserter(lengths), [](string& w) { return w.size(); });
	
	for (auto n : lengths)
		cout << n << " ";
	cout << endl;
	
	
	return 0;
}
