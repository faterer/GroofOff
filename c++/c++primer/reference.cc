#include <iostream>

using namespace std;

int
main(int argc, char *argv[])
{
	int ival = 1.01;
	//int &rval1 = 1.01;
	
	int &rval2 = ival;
	const int &rval3 = 1;
	
	rval2 = 3.14159;
	rval2 = rval3;
	ival = rval3;
	//rval3 = ival;
	
	int i, &ri = i;
	i = 5;
	ri = 10;
	std::cout << i << " " << ri << std::endl;
	
	return 0;
}