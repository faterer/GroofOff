#include <iostream>
#include <functional>
#include <cmath>

using namespace std;
using namespace placeholders;

double logx(int b, double x) {
	return log(x) / log(b);
}

int main()
{
	auto logx2 = bind(logx, 2, _1);
	cout << logx2(16.0) << endl;

	auto g = [](double x) { return logx(2, x); };
	cout << g(16.0) << endl;

	auto logb100 = bind(logx, _1, 100.0);
	cout << "log of 100 with variable base: \n";
	for(int i = 2; i <= 10; ++i) {
		cout << "log of 100 to base " << i << "is" << logb100(i) << endl;
	}

	return 0;
}