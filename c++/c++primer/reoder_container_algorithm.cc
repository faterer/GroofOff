#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
 	//string tmpWords[] = {"the","quick", "red", "fox", "jumps", "over", "the", "slow", "red", "turtle"};
	string s = "the quick red fox jumps over te slow red turtle";
	stringstream strm(s);
	vector<string> words;
	string word;
	while (strm >> word)
		words.push_back(word);
	for (int i = 0; i < words.size(); ++i)
		cout << words[i] << " ";
	cout << endl;
	
	sort(words.begin(), words.end());
	for (int i = 0; i < words.size(); ++i)
		cout << words[i] << " ";
	cout << endl;
	
	vector<string>::iterator end_unique = unique(words.begin(), words.end());
	for (int i = 0; i < words.size(); ++i)
		cout << words[i] << " ";
	cout << endl;

	words.erase(end_unique, words.end());
	for (int i = 0; i < words.size(); ++i)
		cout << words[i] << " ";
	cout << endl;
	
	return 0;
}