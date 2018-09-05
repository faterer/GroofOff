#include <iostream>
#include <string>

class Product
{
public:
    virtual std::string getName() const = 0;
    virtual ~Product() {}
};

class ConcreteProductA : public Product
{
public:
    ~ConcreteProductA() {}
    std::string getName() const {
        return "product A";
    }
};

class ConcreteProductB : public Product
{
public:
    ~ConcreteProductB() {}
    std::string getName() const {
        return "product B";
    }
};

class Factory
{
public:
    virtual Product* createProduct() = 0;
    virtual ~Factory() {};
};

class ConcreteProductAFactory : public Factory
{
public:
    ~ConcreteProductAFactory() {}
    Product* createProduct() {
        return new ConcreteProductA();
    }
};

class ConcreteProductBFactory : public Factory
{
public:
    ~ConcreteProductBFactory() {}
    Product* createProduct() {
        return new ConcreteProductB();
    }
};

int main() 
{
    Factory* fca = new ConcreteProductAFactory();
    Product* pda = fca->createProduct();
    Factory* fcb = new ConcreteProductBFactory();
    Product* pdb = fcb->createProduct();
    std::cout << pda->getName() << std::endl;
    std::cout << pdb->getName() << std::endl;
}
