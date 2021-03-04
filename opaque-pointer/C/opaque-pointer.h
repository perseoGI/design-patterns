/*
 * Example implementation of opaque-pointer patter on C
 *
 */

struct Foo;       // Compiler will consider struct Foo as an incomplete type

// Incomplete types can be used on declarations

int getA (struct Foo *foo);
double getB (struct Foo *foo);
char getC (struct Foo *foo);

void setA (struct Foo *foo, int a);
void setB (struct Foo *foo, double b);
void setC (struct Foo *foo, char c);

void printFoo(struct Foo *foo);

