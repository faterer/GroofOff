#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	string word;
	vector<string> text;
	while (cin >> word)
	{
		text.push_back(word);
	}
	for(vector<string>::size_type ix = 0; ix != text.size(); ++ix)
		cout << text[ix] << endl;
	return 0;
}