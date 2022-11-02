# Factory Method Creational Pattern

Also known as Virtual Constructor

Can be used to create instances of classes without depending on concrete types

## Pros

## Cons

## When to use?

## Implementation

## Parametrized factory

Allows to not declare always a constructor for each class by creating a Factory Class with a method `create`.

This method will receive an input parameter which will tell `create` which derived class to create.


### C++ `std::make_unique`

Comparing this two lines:

```cpp
std::unique_ptr<int> pointer {new int(1)};

auto pointer {std::make_unique<int>(42)};
```

The second line is less error prone, more generic, and yes, it is a factory!

So, C++ `std::make_unique` function is a factory which receives a class type
and return a unique pointer to new object of the type.

Observation: the order of evaluation of parameters is unspecified, but also is
unspecified the evaluation order of the sub expressions of the arguments.

C++17 guarantee that each argument is completely evaluated (but in an unspecified order)

But in previous versions, this code could lead to a memory leak if a new is
performed, but not yet assigned to the smart pointer, a change of context is
done, and the next new throws a runtime exception.

```cpp
foo(std::unique_ptr<int>{new int{1}, 
    std::unique_ptr<double>{new double(32.3)}
    );
```
