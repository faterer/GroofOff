#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<int> ivec;
	vector<int> ivec2(10);
	
	cout << ivec.size() << endl;
	cout << ivec.max_size() << endl;
	cout << ivec2.size() << endl;
	cout << ivec2.max_size() << endl;	
	ivec2.push_back(2);
	cout << ivec2.size() << endl;
	for(vector<int>::size_type ix = 0; ix != ivec2.size(); ++ix)
		cout << ivec2[ix] << endl;
	return 0;
}
