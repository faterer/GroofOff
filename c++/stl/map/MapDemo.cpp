/*
 * MapDemo.cpp
 *
 *  Created on: Dec 22, 2014
 *      Author: mawang
 */
#include <iostream>
#include <map>

using namespace std;

int main()
{
	map<int, string> m;
	m.insert(make_pair(1,"wangmai"));
	m.insert(make_pair(2, "samuel"));
	m.insert(make_pair(3, "guowang"));

	for(auto i : m)
		cout << i.first << ":" << i.second << endl;

	return 0;
}

