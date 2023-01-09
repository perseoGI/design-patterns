#include <iostream>

// RAII: "Resource Acquisition Is Initialization"
template <typename T>
class Pointer
{
    T *m_ptr;

public:
    Pointer(T *ptr)
        : m_ptr{ptr}
    {
    }

    ~Pointer() { delete m_ptr; }

    T *get() { return m_ptr; }

    T *operator->() { return m_ptr; }

    T &operator*() { return *m_ptr; }
};

class Foo
{
public:
    Foo() { std::cout << "Foo()" << std::endl; }
    ~Foo() { std::cout << "~Foo()" << std::endl; }
    void bar() { std::cout << "Hello world" << std::endl; }
};

int main()
{
    Pointer<Foo> foo{new Foo};
    foo.get()->bar();
    foo->bar();
    (*foo).bar();
}
