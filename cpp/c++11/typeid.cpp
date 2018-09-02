#include <iostream>
#include <functional>
#include <typeindex>
#include <string>
#include <unordered_map>

using namespace std;

class Sender{};
class Receiver{};

int main()
{
	int i;
	double d;
	float f;
	string s;
	
	cout << "i: " << typeid(i).name() << endl;
	cout << "d: " << typeid(d).name() << endl;
	cout << "f: " << typeid(f).name() << endl;
	cout << "s: " << typeid(s).name() << endl;
	cout << "Sender: " << typeid(Sender).name() << endl;
	cout << "Receiver: " << typeid(Receiver).name() << endl;	
	
	cout << boolalpha << "compare double to float: " << (typeid(double) == typeid(float)) << endl;
	cout << boolalpha << "compare int to long: " << (typeid(int) == typeid(long)) << endl;
	cout << endl;
	
	//An unordered_map indexed by the type with a lambda expression "value"
	unordered_map<type_index, std::function<string()>> type_func;
	
	type_func[typeid(Sender)] = []() { return "Sender something"; };
	type_func[typeid(Receiver)] = []() { return "Receiver something"; };
	
	for (auto itr = type_func.begin(); itr != type_func.end(); ++itr) {
		//*itr is a std::pair
		cout << (*itr).first.name() << ' ' << (*itr).second() << endl;
	}

	//cout << type_func[type(int)] << endl; //error!!
	cout << boolalpha << (type_func.find(typeid(int)) == type_func.end()) << endl;

	return 0;
}
