#include <iostream>

class Product
{
};

class Builder
{
public:
    virtual void buildPart() = 0;
    virtual ~Builder() = default;
};

class ConcreteBuilder : public Builder
{
    Product *m_pProduct;

public:
    ConcreteBuilder() { std::cout << "[ConcreteBuilder] Created\n"; }

    void buildPart() override
    {
        std::cout << "[ConcreteBuilder] Building...\n";
        std::cout << "\tPart A\n";
        std::cout << "\tPart B\n";
        std::cout << "\tPart C\n";

        m_pProduct = new Product{};
    }
    Product *getResult()
    {
        std::cout << "[ConcreteBuilder] Returning result\n";
        return m_pProduct;
    }
};

class Director
{
    Builder *m_pBuilder;

public:
    Director(Builder *builder)
        : m_pBuilder(builder)
    {
        std::cout << "[Director] Created\n";
    }
    void construct()
    {
        std::cout << "[ConcreteBuilder] construct process started...\n";
        m_pBuilder->buildPart();
        std::cout << "[ConcreteBuilder] construct process finished...\n";
    }
};

int main()
{
    ConcreteBuilder builder;
    Director dir{&builder};
    dir.construct();
    auto *product{builder.getResult()};
    delete product;
}
