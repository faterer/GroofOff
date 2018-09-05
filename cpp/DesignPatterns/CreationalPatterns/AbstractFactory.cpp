#include <iostream>
#include <string>

class AbstractProductA
{
public:
    virtual std::string getName() const = 0;
    virtual ~AbstractProductA() {}     
};

class AbstractProductB
{
public:
    virtual std::string getName() const = 0;
    virtual ~AbstractProductB() {}
};

class ProductA1 : public AbstractProductA
{
public:
    std::string getName() const {
        return "product A1";
    }
    ~ProductA1() {}
};

class ProductA2 : public AbstractProductA
{
public:
    std::string getName() const {
        return "product A2";
    }
    ~ProductA2() {}
};

class ProductB1 : public AbstractProductB
{
public:
    std::string getName() const {
        return "product B1";
    }
    ~ProductB1() {}
};

class ProductB2 : public AbstractProductB
{
public:
    std::string getName() const {
        return "product B2";
    }
    ~ProductB2() {}
};

class AbstractFactory
{
public:
    virtual AbstractProductA* createProductA() = 0;
    virtual AbstractProductB* createProductB() = 0;
    virtual ~AbstractFactory() {}
};

class AbstractFactory1 : public AbstractFactory
{
public:
    AbstractProductA* createProductA() {
        return new ProductA1();
    }
    AbstractProductB* createProductB() {
        return new ProductB1();
    }
    ~AbstractFactory1() {}
};

class AbstractFactory2 : public AbstractFactory
{
public:
    AbstractProductA* createProductA() {
        return new ProductA2();
    }
    AbstractProductB* createProductB() {
        return new ProductB2();
    }
    ~AbstractFactory2() {}
};

int main() {

}
