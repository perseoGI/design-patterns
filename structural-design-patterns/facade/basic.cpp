#include <iostream>

class A
{
public:
    void callA() {}
};

class B
{
public:
    void callB() {}
};

class C
{
public:
    void callC() {}
};

class Facade
{
    A *m_pA;
    B *m_pB;
    C *m_pC;

public:
    Facade()
    {
        m_pA = new A;
        m_pB = new B;
        m_pC = new C;
    }
    ~Facade()
    {
        delete m_pA;
        delete m_pB;
        delete m_pC;
    }
    void use()
    {
        m_pA->callA();
        m_pB->callB();
        m_pC->callC();
    }
};

class Client
{
    Facade *m_pF;

public:
    Client() { m_pF = new Facade; }
    ~Client() { delete m_pF; }
    void invoke() { m_pF->use(); }
};

int main()
{
    return 0;
}
