#include <iostream>

class AbstractProductA
{
public:
    virtual void productA() = 0;
    virtual ~AbstractProductA() = default;
};

class AbstractProductB
{
public:
    virtual void productB() = 0;
    virtual ~AbstractProductB() = default;
};

// Set 1
class ProductA1 : public AbstractProductA
{
public:
    void productA() override { std::cout << "[1] Product A\n"; }
};

class ProductB1 : public AbstractProductB
{
public:
    void productB() override { std::cout << "[1] Product B\n"; }
};

// Set 2
class ProductA2 : public AbstractProductA
{
public:
    void productA() override { std::cout << "[2] Product A\n"; }
};

class ProductB2 : public AbstractProductB
{
public:
    void productB() override { std::cout << "[2] Product B\n"; }
};

int main()
{
    AbstractProductA *pA{new ProductA1{}};
    AbstractProductB *pB{new ProductB1{}};
    pA->productA();
    pB->productB();

    // This is coupled :(
    // Force to update all instances of class names when changing between families
    // AbstractProductA *pA{new ProductA2{}};
    // AbstractProductB *pB{new ProductB2{}};
    // pA->productA();
    // pB->productB();
    return 0;
}
