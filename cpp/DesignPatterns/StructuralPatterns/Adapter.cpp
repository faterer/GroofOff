#include <iostream>

class Target
{
public:
    virtual void request() = 0;
};

class Adaptee
{
public:
    void specificRequest() {
        std::cout << "specific request" << std::endl;
    }
};

class Adapter : public Target
{
public:
    Adapter(Adaptee *adaptee) : adaptee_(adaptee) {}
    virtual ~Adapter() {}
    void request() {
        adaptee_->specificRequest();
    }
private:
    Adaptee *adaptee_;
};

int main() 
{
    Adaptee *adaptee = new Adaptee();
    Target *tar = new Adapter(adaptee);
    tar->request();
    return 0;
}

