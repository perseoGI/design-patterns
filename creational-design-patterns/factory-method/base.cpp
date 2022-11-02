#include <iostream>

class Product
{
public:
    virtual void Operation() = 0;
    virtual ~Product() = default;
};

class ConcreteProduct : public Product
{
    void Operation() override { std::cout << __func__ << std::endl; }
};

class ConcreteProduct2 : public Product
{
    void Operation() override { std::cout << __func__ << std::endl; }
};

class Creator
{
    Product *m_pProduct;

public:
    void anOperation()
    {
        // m_pProduct = new ConcreteProduct{}; // not a good idea, coupling anOperation always with a concrete class
        m_pProduct = Create();  // the instance returned can be from any class inside the hierarchy
        m_pProduct->Operation();
    }
    // Can be made pure virtual but would not be able to create Creator object
    // Factory method
    virtual Product *Create() { return nullptr; };
};

class ConcreteCreator : public Creator
{
    Product *Create() override { return new ConcreteProduct{}; }
};

class ConcreteCreator2 : public Creator
{
    Product *Create() override { return new ConcreteProduct2{}; }
};

int main()
{
    ConcreteCreator ct;
    ct.anOperation();
    ConcreteCreator2 ct2;
    ct2.anOperation();
    return 0;
}
