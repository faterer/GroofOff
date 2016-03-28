/*
 * unique.cpp
 *
 *  Created on: May 7, 2014
 *      Author: mawang
 */
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <locale>
using namespace std;

class bothWhiteSpaces
{
public:
	bothWhiteSpaces(const locale& l) : loc(l)
	{
	}

	bool operator()(char elem1, char elem2)
	{
		return isspace(elem1, loc) && isspace(elem2, loc);
	}

private:
	const locale& loc;
};
/*
int main()
{
	string contents;

	//don't skip leading whitespaces
	cin.unsetf(ios::skipws);

	unique_copy(istream_iterator<char>(cin),
				istream_iterator<char>(),
				back_inserter(contents),
				bothWhiteSpaces(cin.getloc()));
	cout << contents;
}
*/

