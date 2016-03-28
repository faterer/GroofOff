/*
 * BigInteger.hpp
 *
 *  Created on: May 9, 2014
 *      Author: mawang
 */

#ifndef BIGINTEGER_HPP_
#define BIGINTEGER_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <iterator>
#include <algorithm>

using namespace std;

class BigInteger
{
	friend ostream& operator<<(ostream& os, const BigInteger& bi);

public:
	BigInteger() : sign(true)
	{
	}

	BigInteger(const string& s)
	{
		string::size_type i = 0;
		if (s[0] == '-')
		{
			sign = false;
			++i;
		}
		else
		{
			sign = true;
		}

		for (; i < s.length(); ++i)
		{
			bigInt_.push_back(s[i] - '0');
		}
	}

	BigInteger(const BigInteger& bi) : bigInt_(bi.bigInt_), sign(bi.sign)
	{
	}

	BigInteger operator+(BigInteger& rhs);
	BigInteger operator-(BigInteger& rhs);
	BigInteger operator*(BigInteger& rhs);
	BigInteger operator/(BigInteger& rhs);
	BigInteger& operator++(); //++BigInteger
	BigInteger& operator++(int); // BigIntger++

	bool operator>(const BigInteger& rhs) const;


private:
	vector<int> bigInt_;
	bool sign;
};

bool isNotZero(int v)
{
	return v != 0 ? true : false;
}

ostream& operator<<(ostream& os, const BigInteger& bi)
{
	if (!bi.sign)
	{
		os << '-';
	}

	vector<int>::const_iterator pos1;
	pos1 = find_if(bi.bigInt_.begin(), bi.bigInt_.end(), isNotZero);

	vector<int> vp(pos1, bi.bigInt_.end());

	for(vector<int>::size_type i = 0; i < vp.size(); ++i)
	{
		os << vp[i];
	}

	return os;
}

BigInteger BigInteger::operator+(BigInteger& rhs)
{
	if (sign == rhs.sign)
	{
		vector<int>	v1(bigInt_);
		vector<int> v2(rhs.bigInt_);
		reverse(v1.begin(), v1.end());
		reverse(v2.begin(), v2.end());
		if (v1.size() > v2.size())
		{
			v2.resize(v1.size(), 0);
		}
		else
		{
			v1.resize(v2.size(), 0);
		}
		vector<int>::iterator pos1, pos2;
		int c = 0;
		BigInteger s;
		for(pos1 = v1.begin(), pos2 = v2.begin(); pos1 != v1.end(); ++pos1,++pos2)
		{
			int a = *pos1 + *pos2;
			int b = (a + c) % 10;
			c = (a + c) / 10;
			s.bigInt_.push_back(b);
		}
		if (c > 0)
			s.bigInt_.push_back(c);
		reverse(s.bigInt_.begin(), s.bigInt_.end());
		s.sign = sign;
		return s;
	}
	else
	{
		sign ? rhs.sign = true : sign = true;
		return *this - rhs;
	}
}

vector<int> BigIntMinus(const vector<int>& v1, const vector<int>& v2)
{
	vector<int> result;
	int a;
	int c = 0;
	for (vector<int>::size_type i= 0; i < v1.size(); ++i)
	{
		a = (v1[i] - v2[i] - c) >= 0 ? (v1[i] - v2[i] - c) : (10 + v1[i] - v2[i] - c);
		c = (v1[i] - v2[i] - c) >= 0 ? 0 : 1;
		result.push_back(a);
	}
	return result;
}


BigInteger BigInteger::operator-(BigInteger& rhs)
{

	if (sign == rhs.sign)
	{
		vector<int>	v1(bigInt_);
		vector<int> v2(rhs.bigInt_);
		reverse(v1.begin(), v1.end());
		reverse(v2.begin(), v2.end());
		BigInteger s;
		if (v1.size() > v2.size())
		{
			v2.resize(v1.size(), 0);
			s.bigInt_ = BigIntMinus(v1, v2);
			s.sign = sign;
		}
		else if(v1.size() == v2.size())
		{
			if (v1 > v2)
			{
				s.bigInt_ = BigIntMinus(v1, v2);
				s.sign = sign;
			}
			else
			{
				s.bigInt_ = BigIntMinus(v2, v1);
				rhs.sign ? s.sign = false : s.sign = true;
			}
		}
		else
		{
			v1.resize(v2.size(), 0);
			s.bigInt_ = BigIntMinus(v2, v1);
			rhs.sign ? s.sign = false : s.sign = true;
		}
		reverse(s.bigInt_.begin(), s.bigInt_.end());
		return s;
	}
	else
	{
		if (sign)
		{
			BigInteger tmp(rhs);
			tmp.sign = true;
			return *this + tmp;
		}
		else
		{
			BigInteger tmp(rhs);
			tmp.sign = true;
			return tmp - *this;
		}
	}
}

/*
bool BigInteger::operator>(const BigInteger& rhs) const
{
	bool result;


	return result;
}
*/
#endif /* BIGINTEGER_HPP_ */
