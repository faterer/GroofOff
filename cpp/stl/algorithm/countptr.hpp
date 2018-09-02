#ifndef COUNTED_PTR_HPP
#define COUNTED_PTR_HPP

template <typename T>
class CountedPtr
{
public:
	//initialize pointer with existing pointer
	//- requires that the pointer p is a return value of new
	explicit CountedPtr(T* p = 0)
		: ptr(p), count(new long(1))
	{
	}

	//copy pointer (one more owner)
	CountedPtr (const CountedPtr<T>& p) throw()
		: ptr(p.ptr), count(p.count)
	{
		++*count;
	}

	// destructor (delete value if this was the last owner)
	~CountedPtr () throw()
	{
		dispose();
	}

	//
	CountedPtr<T>& operator= (const CountedPtr<T>& p) throw()
	{
		if (this != &p)
		{
			dispose();
			ptr = p.ptr;
			count = p.count;
			++*count;
		}
		return *this;
	}

	T& operator*() const throw()
	{
		return *ptr;
	}

	T& operator->() const throw()
	{
		return ptr;
	}

private:
	T* ptr;
	long* count;
	void dispose()
	{
		if (--*count == 0)
		{
			delete count;
			delete ptr;
		}
	}
};

#endif  //COUNTED_PTR_HPP
