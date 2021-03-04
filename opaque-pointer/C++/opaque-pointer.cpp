#include "opaque-pointer.h"
#include <memory>

struct Foo::ChesireCat {
   int a;
   double b;
   char c;
};

Foo::Foo() : d_ptr_(std::make_unique<ChesireCat>()){ }

Foo::Foo(const Foo &foo) : d_ptr_(std::make_unique<ChesireCat>(*foo.d_ptr_)){ }

Foo::Foo(Foo &&foo) = default;

Foo & Foo::operator= (const Foo &foo) {
   *d_ptr_ = *foo.d_ptr_;
   return *this;
}

Foo & Foo::operator= (Foo &&foo) = default;

Foo::~Foo() = default;

int Foo::getA (void){
   return d_ptr_->a;
}

double Foo::getB (void){
   return d_ptr_->b;
}

char Foo::getC (void){
   return d_ptr_->c;
}

void Foo::setA (int a){
   d_ptr_->a = a;
}

void Foo::setB (double b){
   d_ptr_->b = b;
}

void Foo::setC (char c){
   d_ptr_->c = c;
}

std::ostream& operator<< (std::ostream &os, Foo f){
   return os << "Foo: { " << "a: " << f.d_ptr_->a << ", b: " << f.d_ptr_->b <<
      ", c: " << f.d_ptr_->c << " }" <<std::endl;
}


