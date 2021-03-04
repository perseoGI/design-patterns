#include <iostream>
#include "opaque-pointer.h"


int main () {

   Foo foo;

   std::cout << foo;

   foo.setA(1);
   foo.setB(63.235);
   foo.setC('C');

   std::cout << "After setter" << std::endl;
   std::cout << foo;

   return 0;
}
