#include <iostream>

class Singleton
{
public:
    static Singleton * getInstance() {
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }

    void print() {
        std::cout << "singleton" << std::endl;
    }

private:
    Singleton() {}
    static Singleton *instance;
};

Singleton* Singleton::instance = nullptr;

int main()
{
    Singleton::getInstance()->print();
}