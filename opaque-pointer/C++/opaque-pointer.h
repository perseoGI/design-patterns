/*
 * Example implementation of opaque-pointer patter on C++
 *
 * NOTE: needs C++14
 *
 */
#include <memory>
#include <iostream>

class Foo
{
public:
    Foo();                           // Constructor
    Foo(const Foo &foo);             // Copy constructor
    Foo(Foo &&foo);                  // Move constructor
    Foo &operator=(const Foo &foo);  // Assignment operator
    Foo &operator=(Foo &&foo);       // Move assignment operator
    ~Foo();                          // Destructor

    int getA(void);
    double getB(void);
    char getC(void);

    void setA(int a);
    void setB(double b);
    void setC(char c);

    friend std::ostream &operator<<(std::ostream &os, Foo f);

private:
    struct ChesireCat;                   // Not defined here (hidded)
    std::unique_ptr<ChesireCat> d_ptr_;  // Opaque pointer
};
