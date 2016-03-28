/*
 * foreach3.cpp
 *
 *  Created on: Apr 25, 2014
 *      Author: mawang
 */

#include "algostuff.hpp"

using namespace std;

class MeanValue
{
public:
	MeanValue()
		: sum(0), num(0)
	{
	}

	void operator()(int elem)
	{
		num++;
		sum += elem;
	}

	operator double()
	{
		return static_cast<double>(sum) / static_cast<double>(num);
	}

private:
	long sum;
	long num;
};

/*
int main()
{
	vector<int>	coll;

	INSERT_ELEMENTS(coll, 1, 8);

	double mv = for_each(coll.begin(), coll.end(), MeanValue());

	cout << "Mean Value:" << mv << endl;
}
*/
