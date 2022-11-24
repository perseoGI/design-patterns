# Factory Method Creational Pattern

Also known as Virtual Constructor

Can be used to create instances of classes without depending on concrete types

![factory-method-structure](https://user-images.githubusercontent.com/26503843/203759340-b80a384f-941b-4b07-b0ac-3802a33c8609.png)


## Pros

- Instances can be created at runtime
- Promotes loos coupling: the name of the classes does not have to be hardcoded
- Construction becomes simpler due to abstraction
- Construction process is encapsulated
- Modify not return a new instance every time called (can return a cached instance for example -> object pools)

## Cons

- Every time a new product is added, it will be needed to add a corresponding
  factory class -> can be avoided using a parametrized factory method

## When to use?

- When a class does not know which instances it needs at runtime
- A class does not want to depend on the concrete classes that it uses
- Encapsulate the creation process
- Clients implement the classes that you use and you need to create  instances of such classes (useful for frameworks)

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

This could be a custom implementation of `std::make_unique`:

```cpp
template<typename T, typename ...Args>
std::unique_ptr<T> Make_unique(Args &...args){
    // Use std::forward to retain the type information of the arguments
    return std::unique_ptr<T>{new T{std::forward<Args>(args)...}};
}
```

### C++ `std::make_shared`

The following line needs two allocations because a shared pointer needs more space than the variable its pointing to itself 
just to manage a reference counter.

```cpp
std::shared_ptr<int> ptr {new int(4)};
```

Using the factory method `std::make_shared`, we are not only benefiting from
using a factory method but increasing performance by only allocating space for
variable size + shared pointer metadata at once. And also having to free memory
once.

```cpp
auto ptr {std::make_shared<int>(4)};
```

There are many `std::make_...` in C++ 
No needed in C++17 with the feature called _Compile time argument deduction_
which allows determine the type of template arguments.
- `std::make_pair` 
- `std::make_tuple` 

```cpp
std::multimap<int,std::string> m;
m.insert(std::pair{3,"hello"});
std::tuple t{1, "hola", 3.43f};
```
