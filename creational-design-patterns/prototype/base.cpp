#include <iostream>

class Prototype
{
public:
    virtual Prototype *clone() = 0;
    virtual ~Prototype() = default;
};

class ConcretePrototype1 : public Prototype
{
public:
    ConcretePrototype1 *clone() override
    {
        std::cout << "ConcretePrototype1::clone\n";
        return new ConcretePrototype1{*this};
    }
};

class ConcretePrototype2 : public Prototype
{
public:
    ConcretePrototype2 *clone() override
    {
        std::cout << "ConcretePrototype2::clone\n";
        return new ConcretePrototype2{*this};
    }
};

class Client
{
    Prototype *prototype;

public:
    void setPrototype(Prototype *p) { prototype = p; }

    void operation() { auto p{prototype->clone()}; }
};

int main()
{
    Client c;
    c.setPrototype(new ConcretePrototype1{});
    c.operation();
}
