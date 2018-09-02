#include <iostream>

class Product
{
public:
    virtual std::string getName() const = 0;
    virtual ~Product() {};
};

class ConcreteProductA()
{
public:
    std::string getName() {
        return "product A";
    }
};

class ConcreteProductB()
{
public:
    std::string getName() {
        return "product B";
    }
};

class Factory
{
public:
    virtual Product* createProduct() const = 0;
    virtual ~Factory() {};
};

class ConcreteProductAFactory()
{
public:
    Product* createProduct() {
        return new ConcreteProductA();
    }
}

class ConcreteProductBFactory()
{
public:
    Product* createProduct() {
        return new ConcreteProductB();
    }
}

int main() 
{
    Factory* fca = new ConcreteProductAFactory();
    Product* pda = fca->createProduct();
    Factory* fcb = new ConcreteProductBFactory();
    Product* pdb = fcb->createProduct();
    std::cout << pda->getName() << std::endl;
    std::cout << pdb->getName() << std::endl;
}