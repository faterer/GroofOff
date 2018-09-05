#include <iostream>
//#include <boost/noncopyable.hpp>
#include <string>
#include <pthread.h>
#include <stdlib.h> // atexit

//use pthread_once make thread safe singleton from Muduo
//Singleton<T>::instance()
template<typename T>
class Singleton
{
public:
	static T& instance()
	{
		// std::call_once(&callonce_, &Singleton::init); c++11
		pthread_once(&ponce_, &Singleton::init); 
		return *value_;
	}

private:
	Singleton();
	~Singleton();

	static void init()
	{
		value_ = new T();
		::atexit(destroy); // pointer to a function to be called on normal program termination
	}

	static void destroy()
	{
		delete value_;
	}

private:
	static pthread_once_t ponce_; //static std::once_flag callonce_;
	static T*			  value_;
};

template<typename T>
pthread_once_t Singleton<T>::ponce_ = PTHREAD_ONCE_INIT;

template<typename T>
T* Singleton<T>::value_ = NULL;

class Test
{
public:
	Test() {}
	~Test() {}

	const std::string& name() const { return name_; }
	void setName(const std::string& n) { name_ = n; }
private:
	std::string name_;
};

int main()
{
	Singleton<Test>::instance().setName("only one");
	std::cout << Singleton<Test>::instance().name() << std::endl;
}