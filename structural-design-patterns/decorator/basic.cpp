#include <iostream>

class Component
{
public:
    virtual void operation() = 0;
    virtual ~Component() = default;
};

class ConcreteComponent : public Component
{
public:
    void operation() override { std::cout << "ConcreteComponent::operation\n"; }
};

class Decorator : public Component
{
    Component *m_ptr{};

// protected: // or just make the constructor protected -> cant be used with C++11 constructor inheritance
public:
    Decorator(Component *ptr)
        : m_ptr{ptr}
    {
    }

// public:
//     void operation() override;
    void operation() override = 0;  // make an abstract class but define it anyway to forbid Decorator instantiation
};

void Decorator::operation() { 
    m_ptr->operation();
}

class ConcreteDecoratorA : public Decorator
{
    using Decorator::Decorator;

public:
    void operation() override
    {
        std::cout << "ConcreteDecoratorA::operation\n";
        Decorator::operation();
    };
};

class ConcreteDecoratorB : public Decorator
{
    // using Decorator::Decorator;
    std::string state{"hello"};
public:
    ConcreteDecoratorB(Component *comp) : Decorator(comp) {}

    void operation() override
    {
        std::cout << "ConcreteDecoratorB::operation\n";
        Decorator::operation();
    };

    void otherOperation() { std::cout << "ConcreteDecoratorB::otherOperation " << state << '\n'; }
};

// Client abstraction layer
void operate(Component *comp){
    comp->operation();
}

int main()
{
    ConcreteComponent component{};
    // Decorator dec{&component}; // cant be instantiated

    ConcreteDecoratorA decA{&component};
    decA.operation();

    ConcreteDecoratorB decB{&decA};
    decB.operation();
    decB.otherOperation();

    operate(&decA);
}
