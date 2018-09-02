/*
 * Queue.hpp
 *
 *  Created on: May 5, 2014
 *      Author: mawang
 */
#include <deque>
#include <exception>

template<typename T>
class Queue
{
  public:
	class ReadEmptyQueue : public std::exception
	{
	  public:
		virtual const char* what() const throw()
		{
			return "read empty queue";
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
			throw ReadEmptyQueue();
		}
		T elem(c.front());
		c.pop_front();
		return elem;
	}

	T& front()
	{
		if (c.empty())
		{
			throw ReadEmptyQueue();
		}
		return c.front();
	}

  protected:
	std::deque<T> c;
};



