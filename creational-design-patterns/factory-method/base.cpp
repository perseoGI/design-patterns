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

class Creator
{
    Product *m_pProduct;

public:
    void AnOperation
};
