#include <iostream>

class Subject
{
public:
    virtual void request() = 0;
    virtual ~Subject() = default;
};

class RealSubject : public Subject
{
public:
    void request() override { std::cout << "[RealSubject] request processed\n"; }
};

class Proxy : public Subject
{
    RealSubject *m_pSubject{nullptr};

public:
    ~Proxy() { delete m_pSubject; }
    void request() override
    {
        if (m_pSubject == nullptr) {
            std::cout << "[Proxy] creating RealSubject\n";
            m_pSubject = new RealSubject{};
        }
        std::cout << "[Proxy] request processed\n";
        m_pSubject->request();
    }
};

void operate(Subject *s)
{
    s->request();
}

int main()
{
    RealSubject *sub{new RealSubject{}};
    operate(sub);

    Subject *subProxy{new Proxy{}};
    operate(subProxy);
}
