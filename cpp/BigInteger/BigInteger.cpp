/*
 * BigInteger.cpp
 *
 *  Created on: May 8, 2014
 *      Author: mawang
 */
#include "BigInteger.hpp"

void TestPrint()
{
	BigInteger bigInt1("123");
	BigInteger bigInt2("-123");
	cout << bigInt1 << endl;
	cout << bigInt2 << endl;
}

void TestAdd()
{
	BigInteger bigInt1("123456789");
	BigInteger bigInt2("987654321");
	BigInteger bigInt3("623456789");
	BigInteger bigInt4("987");
	BigInteger bigInt5("923");
	BigInteger bigInt6("77");
	BigInteger bigInt7("-923");
	BigInteger bigInt8("-77");
	BigInteger bigInt9("-923");
	BigInteger bigInt10("77");
	cout << bigInt1 << " + "<< bigInt2 << " = "<< bigInt1 + bigInt2 << endl;
	cout << bigInt3 << " + "<< bigInt4 << " = "<< bigInt3 + bigInt4 << endl;
	cout << bigInt5 << " + "<< bigInt6 << " = "<< bigInt5 + bigInt6 << endl;
	cout << bigInt6 << " + "<< bigInt5 << " = "<< bigInt6 + bigInt5 << endl;
	cout << bigInt7 << " + "<< bigInt8 << " = "<< bigInt7 + bigInt8 << endl;
	cout << bigInt9 << " + "<< bigInt10 << " = "<< bigInt9 + bigInt10 << endl;
}

void TestMinus()
{
	BigInteger bigInt1("123");
	BigInteger bigInt2("23");
	BigInteger bigInt3("-123");
	BigInteger bigInt4("-23");
	BigInteger bigInt5("123");
	BigInteger bigInt6("111");
	BigInteger bigInt7("2456");
	BigInteger bigInt8("999");
	BigInteger bigInt9("2456");
	BigInteger bigInt10("-999");
	cout << bigInt1 << " - " << bigInt2 << " = " << bigInt1 - bigInt2 << endl;
	cout << bigInt2 << " - " << bigInt1 << " = " << bigInt2 - bigInt1 << endl;
	cout << bigInt3 << " - " << bigInt4 << " = " << bigInt3 - bigInt4 << endl;
	cout << bigInt4 << " - " << bigInt3 << " = " << bigInt4 - bigInt3 << endl;
	cout << bigInt5 << " - " << bigInt6 << " = " << bigInt5 - bigInt6 << endl;
	cout << bigInt6 << " - " << bigInt5 << " = " << bigInt6 - bigInt5 << endl;
	cout << bigInt7 << " - " << bigInt8 << " = " << bigInt7 - bigInt8 << endl;
	cout << bigInt9 << " - "<< bigInt10 << " = " << bigInt9 - bigInt10 << endl;
}

int main()
{
	TestPrint();
	//TestAdd();
	TestMinus();
}

