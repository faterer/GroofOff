#include <iostream>
#include <type_traits>

using namespace std;

/*
is_arithmetic: integer or floating point, e.g. bool, char, int, long, float, double
is_compound: all non-foundamental. e.g. class/struct, enum, function, pointers, refereneces
is_fundamental: arithmetic, void, nullptr
is_member_pointer: pointer to member
is_object: All non-void, non-function, non-reference types
is_reference: lvalue or rvalue references, i.e. & or &&
is_scalar: includes arithmetic, pointers, member pointer, enum and nullptr
*/

enum class A { };
struct X { };

int main() {
	cout << boolalpha << "is_arithmetic int: " << is_arithmetic<int>::value << endl;
	cout << boolalpha << "is_arithmetic enum class A: " << is_arithmetic<A>::value << endl;
	
	cout << boolalpha << "is_compound X: " << is_compound<X>::value << endl;
	cout << boolalpha << "is_compound double: " << is_compound<double>::value << endl;
	
	cout << boolalpha << "is_fundamental void: " << is_fundamental<void>::value << endl;
	cout << boolalpha << "is_fundamental void*: " << is_fundamental<void*>::value << endl;
	
	cout << boolalpha << "is_member_pointer char X::*: " << is_member_pointer<char X::*>::value << endl;
	cout << boolalpha << "is_member_pointer X*: " << is_member_pointer<X*>::value << endl;
	
	cout << boolalpha << "is_object enum class A: " << is_object<A>::value << endl;
	cout << boolalpha << "is_object X&: " << is_object<X&>::value << endl;
	
	cout << boolalpha << "is_reference char&: " << is_reference<char&>::value << endl;
	cout << boolalpha << "is_reference char&&: " << is_reference<char&&>::value << endl;
	
	cout << boolalpha << "is_scalar decltype(nullptr): " << is_scalar<decltype(nullptr)>::value << endl;
	cout << boolalpha << "is_scalar enum class A: " << is_scalar<A>::value << endl;	
	
	static_assert(is_scalar<A>::value, "X is not a scalar");
	
	return 0;
}
