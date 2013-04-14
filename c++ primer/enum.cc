#include <iostream>

using namespace std;

enum Points
{
	point2d = 2,
	point2w,
	point3d = 3,
	point3w
};

int
main(int argc, char *argv[])
{
	std::cout << point2d 
			  << point2w
			  << point3d
			  << point3w
			  << std::endl;
	return 0;
}