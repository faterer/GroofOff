/*
 * foreach2.cpp
 *
 *  Created on: Apr 25, 2014
 *      Author: mawang
 */

#include "algostuff.hpp"

using namespace std;

template <typename T>
class AddValue
{
public:
	AddValue(const T& v) : theValue_(v)
	{
	}

	void operator()(T& elem) const
	{
		elem += theValue_;
	}
private:
	T theValue_;
};

/*
int main()
{
	vector<int> coll;

	INSERT_ELEMENTS(coll, 1, 9);

	for_each(coll.begin(), coll.end(), AddValue<int>(10));
	PRINT_ELEMENTS(coll);

	for_each(coll.begin(), coll.end(), AddValue<int>(*coll.begin()));
	PRINT_ELEMENTS(coll);
}
*/

