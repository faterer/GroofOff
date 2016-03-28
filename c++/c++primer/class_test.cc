#include <iostream>
#include <string>

class Foo {

};

class Student {

public:
	Student(const std::string& phone_number,
			const std::string& addr,
			const std::string& company,
			const std::string& university)
	: phone_number_(phone_number),
	  addr_(addr),
	  company_(company),
	  university_(university)
	{
	
	}
	
	
	void Print() const
	{
		std::cout << "Phone: " << phone_number_ << std::endl
				  << "Address: " << addr_ << std::endl
				  << "Company: " << company_ << std::endl
				  << "University: " << university_ << std::endl;
	}
    
private:
	std::string phone_number_;
	std::string addr_;
	std::string company_;
	std::string university_;
};

int main()
{
	Student student1("123","chengdu","nsn","scu");
	Student student2("234","chongqin","nokia","cqu");
	student1.Print();	
	student2.Print();
	return 0;
}