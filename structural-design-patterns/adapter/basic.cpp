#include <iostream>

class Target
{
public:
    virtual void request() = 0;
    virtual ~Target() = default;
};

void client(Target *pTarget)
{
    pTarget->request();
}

class Adaptee
{
public:
    void specificRequest() { std::cout << "[Adaptee] Specific request" << '\n'; }
};

class ObjectAdapter : public Target
{
    Adaptee m_adaptee;

public:
    void request() override
    {
        std::cout << "[ObjectAdapter] calling SpecificRequest" << '\n';
        m_adaptee.specificRequest();
    }
};

class ClassAdapter : public Target, public Adaptee
{
public:
    void request() override
    {
        std::cout << "[ClassAdapter] calling SpecificRequest directly" << '\n';
        specificRequest();
    }
};

int main()
{
    ObjectAdapter oAdapter;
    client(&oAdapter);
    ClassAdapter cAdapter;
    client(&cAdapter);
}
