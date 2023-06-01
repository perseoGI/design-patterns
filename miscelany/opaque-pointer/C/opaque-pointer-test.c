#include "opaque-pointer.h"
#include <stdio.h>

int main() {

   struct Foo *foo; // compiler wont let you declare a struct Foo variable as it
                    // is an incomplete type (does not know the size of it)

   setA(foo, 1);
   setB(foo, 63.235);
   setC(foo, 'C');

   printf("After setter\n");
   printFoo(foo);

   return 0;
}
