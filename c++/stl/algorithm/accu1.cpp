/*
 * accu1.cpp
 *
 *  Created on: May 2, 2014
 *      Author: mawang
 */
#include "algostuff.hpp"
using namespace std;

int main()
{
	vector<int>	coll;
	INSERT_ELEMENTS(coll,1,9);
	PRINT_ELEMENTS(coll);

	cout << "sum: "
		 << accumulate(coll.begin(), coll.end(), 0)
		 << endl;
	cout << "sum: "
		 << accumulate(coll.begin(), coll.end(), -100)
		 << endl;
	cout << "product: "
		 << accumulate(coll.begin(), coll.end(), 1, multiplies<int>())
		 << endl;
	cout << "product: "
		 << accumulate(coll.begin(), coll.end(), 0, multiplies<int>())
		 << endl;

}