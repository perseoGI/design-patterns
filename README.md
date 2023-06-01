# Programming Design Patterns

This is just a simple compilation of programming design patterns

## Pattern

Language & domain independent strategies for solving common OO design problems

### UML

#### Composition 

Class contains objects of other class, when it is destroyed, the contained objects will also be destroyed
eg.

Paragraph contains sentence 

```
Paragraph  <.>--- Sentence
```

#### Aggregation

Same as composition but when the instance is destroyed, the aggregated instances are not destroyed

```
Car < >---- Passenger
```

#### Association

Represent relationships between classes, but does not imply a class holds another class

```
                 uses
Application  ------------  Database
```

Driver uses feature of car

```

           drives
Driver  ------------>  Car
```

## SOLID Principles

Design classes and relationships

### Single Responsibility Principle

- A class should have only one reason to change
- Should only have one responsibility
- Having more than one will break with minor changes

```cpp
class Notes{
    void add(){}
    void remove(){}
    void dispaly(){}    // Display can be performed in many different ways
};
```

Solution
```cpp
class Notes{
    void add(){}
    void remove(){}
};

class View{
    void display(Notes &notes){}
};
```

### Open-Close Principle

- Modules should be open for extension but close for modification
- Add new code to change or add features but not change existing code

```cpp
class Notes{
    void add(){
        if(conains('!'){/*...*/}  // modify existing function breaks O-C principle
    }
    void remove(){}
};
```

Solution
```cpp
class Notes{
    virtual void add(){}
    void remove(){}
};

class TagedNotes : public Notes {
    void add() override {
        if(conains('!'){/*...*/}
    }
    void remove(){}
};
```

### Liskov-Substitution Principle

- Subtypes must be substitutable for their base types
- Ensure a subclass has all the behaviors the base class has
- It should provide a different behavior than the base class has but it should not change or modify behavior
    - Changing behaviour could mean that, even returning the same type, that type could be understood in a different way
- By following Liskov principle, we automatically follow Open-Close Principle

```cpp
class Operation {
    virtual int ResultOf(int *begin, int *end){}
};

void Operate(Operation *op) {
    int arr[4]{};
    auto result = op->ResultOf(begin(arr), end(arr));
    std::cout << result;
}
```

Suppose we need to add a boolean operator:

```cpp
class BoolOperation : public Operation {
    int ResultOf(int *begin, int *end) override {
        // return bool
    }
};

// We had to modify existing code (Operate) when creating BoolOperation -> violates Open-Close principle
// BoolOperation cannot be substitutable by Operation -> violates Liskov-Substitution principle
void Operate(Operation *op) {
    int arr[4]{};
    auto result = op->ResultOf(begin(arr), end(arr));
    if(typeid(*op) == typeid(BoolOperation)){       // -> this breaks Liskov
        // assume bool
    } else{
        // assume int
    }
}
```

Solution
```cpp

using ReturnType = std::variant<int, bool>;

struct IOperation {
    virtual ReturnType resultOf(int *begin, int *end) = 0;
    virtual ~IOperation() = default;
};

struct SumOperation : IOperation {
    ReturnType resultOf(int *begin, int *end) { return std::accumulate(begin, end, 0); }
};

struct BoolOperation : IOperation {
    virtual ReturnType resultOf(int *begin, int *end)
    {
        return true;
    }
};

// helper type for the visitor
template <class... Ts>
struct overloaded : Ts... {
    using Ts::operator()...;
};
template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

void operate(IOperation *op)
{
    int arr[4]{1, 2, 3, 4};
    auto result = op->resultOf(std::begin(arr), std::end(arr));
    // Use visitation for type safe access

    std::visit(overloaded{
                   [](int result) { std::cout << "Integer: " << result << '\n'; },
                   [](bool result) { std::cout << "Boolean: " << std::boolalpha << result << '\n'; },
               },
               result);
}
```

### Interface Segregation Principle

- Clients should not be forced to depend on methods they don't use 
- An interface with too many methods will be complex to use (fat interface)
- Separate the interface and put methods based on the client usage

```cpp
struct IFile {
    virtual void read() = 0;
    virtual void write() = 0;
    virtual ~IFile() = default;
};
```
Fat interface, some users will just simply want to read

```cpp
struct IRead {
    virtual void read() = 0;
    virtual ~IRead() = default;
};

struct IWrite {
    virtual void write() = 0;
    virtual ~IWriet() = default;
};
```

### Dependency Inversion Prinnciple

- Abstractions should not depend on details. Details should depend on abstractions.
    - Abstractions => interfaces
    - Details => classes
- Program the interface not the implementation
- Using concrete class directly creates a dependency -> difficult to modify
- Invert the dependency by using an interface rather a concrete class


```cpp
class ImageReader {
    virtual void decode() = 0;
    virtual ~ImageReader() = default;
};

class BitmapReader : public ImageReader {
    void decode() override{}
};

class ImageViewer {
    BitmapReader *m_reader{};   // Dependency
    void display(){}
}
```
Violated Open-Close and Liskov-Substitution principles

Solution

```cpp
class ImageViewer {
    ImageReader *m_reader{};  // Now relay on the abstract interface 
    void display(){}
}
```
