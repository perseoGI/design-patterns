#include <stdio.h>
#include "opaque-pointer.h"


struct Foo {
    int a;
    double b;
    char c;
};



int getA (struct Foo *foo){
    return foo->a;
}
double getB (struct Foo *foo){
    return foo->b;
}
char getC (struct Foo *foo){
    return foo->c;
}

void setA (struct Foo *foo, int a){
    foo->a = a;
}
void setB (struct Foo *foo, double b) {
    foo->b = b;
}
void setC (struct Foo *foo, char c) {
    foo->c = c;
}

void printFoo(struct Foo *foo){
    printf("Foo: { a: %d, b: %lf, c: %c }\n", foo->a, foo->b, foo->c);
}
