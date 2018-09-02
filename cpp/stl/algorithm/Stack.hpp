/*
 * Stack.hpp
 *
 *  Created on: May 5, 2014
 *      Author: mawang
 */

#ifndef STACK_HPP
#define STACK_HPP

#include <deque>
#include <exception>

template<typename T>
class Stack
{
  public:
	class ReadEmptyStack : public std::exception
	{
	  public:
		virtual const char* what() const throw()
		{
			return "read empty stack";
		}
	};

	typename std::deque<T>::size_type size() const
	{
		return c.size();
	}

	bool empty() const
	{
		return c.empty();
	}

	void push(const T& elem)
	{
		c.push_back(elem);
	}

	T pop()
	{
		if (c.empty())
		{
			throw ReadEmptyStack();
		}
		T elem(c.back());
		c.pop_back();
		return elem;
	}

	T& top()
	{
		if (c.empty())
		{
			throw ReadEmptyStack();
		}
		return c.back();
	}

  protected:
	std::deque<T> c;
};




#endif /* STACK_HPP */
