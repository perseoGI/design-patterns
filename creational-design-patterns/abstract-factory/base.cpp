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

class DatabaseFactory
{
public:
    virtual AbstractProductA *createProductA() = 0;
    virtual AbstractProductB *createProductB() = 0;
    virtual ~DatabaseFactory() = default;
};

class SqlServerFactory : public DatabaseFactory
{
public:
    AbstractProductA *createProductA() override { return new ProductA1{}; }
    AbstractProductB *createProductB() override { return new ProductB1{}; }
};

class ConcreteFactory2 : public DatabaseFactory
{
public:
    AbstractProductA *createProductA() override { return new ProductA2{}; }
    AbstractProductB *createProductB() override { return new ProductB2{}; }
};

// This code will never change!
void usePattern(DatabaseFactory *pFactory)
{
    // Enforces the products you get will always bee from same set or family
    AbstractProductA *pA{pFactory->createProductA()};
    AbstractProductB *pB{pFactory->createProductB()};
    pA->productA();
    pB->productB();

    delete pA;
    delete pB;
}

int main()
{
    DatabaseFactory *pFactory{new ConcreteFactory2{}};
    // No longer coupled
    usePattern(pFactory);
    delete pFactory;

    return 0;
}
