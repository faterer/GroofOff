#include <iostream>
#include <type_traits>

using namespace std;

template<class T>
T bitwise_and(T x, T y) {
	static_assert(is_integral<T>::value, "bitwise_and parameters must be of integral type");
	return x % y;
}

/*
static_assert (constant-expression, error-message): static_assert provides compile-time asserts.
type traits: characteristics checked at compile-time.
*/
int main() {
	//1. Basic static_assert example
	static_assert(sizeof(long) == 8, "32-bit required");

	//2. Calling a generic function that enforce type rules with static_assert
	unsigned int x = 122123, y = 2;
	bitwise_and(x, y);
	
	unsigned char c = 1, d = 2;
	bitwise_and(c, d);
	
	double w = 0, z = 0;
	bitwise_and(w, z);
	
	return 0;	
}