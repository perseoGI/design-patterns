# Programming Design Patterns

This is just a simple compilation of programming design patterns


## Pattern

Language & domain independent strategies for solving common OO design problems

### UML

#### Composition 

Class contains objects of other class, when it is destroyed, the contained objects will also be destroyed
eg.
Paragraph contains sentence 

Paragraph  <.>--- Sentence


#### Aggregation

Same as composition but when the instance is destroyed, the aggregated instances are not destroyed

Car < >---- Passenger


#### Association

Represent relationships between classes, but does not imply a class holds another class

```
                   uses
Application    ------------   Database
```

Driver uses feature of car

```

                   drives
      Driver    ------------>   Car
```



## SOLID Principles

Design classes and relationships

### Single Responsibility Principle

A class should have only one reason to change
Should only have one responsibility
Having more than one will break with minor changes

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

Modules should be open for extension but close for modification
Add new code to change or add features but not change existing code

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

Subtypes must be substitutable for their base types
Ensure a subclass has all the behaviors the base class has
It should provide a different behavior than the base class has
But it should not change or modify behavior

Automatically follow Open-Close Principle

```cpp
class Operation {
    virtual int ResultOf(int *begin, int *end){}
};

void Operate(Operation *op) {
    int arr[4]{};
    auto result = op->ResultOf(begin(arr), end(arr));
    std::cout << result;
}

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

using ReturnType = std::variant<int,bool>;

class IOperation {
    virtual ReturnType ResultOf(int *begin, int *end) = 0;
    virtual ~ReturnType() = default;
};

class Operation : IOperation {
    virtual int ResultOf(int *begin, int *end){ /* return int */ } 
};

class BoolOperation : IOperation {
    virtual int ResultOf(int *begin, int *end){ /* return bool */ }
};

```

### Interface Segregation Principle

Clients should not be forced to depend on methods they dont use 

An interface with too many methods will be complex to use (fat interface)

-> Separate the interface and put methods based on the client usage

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

Abstractions should not depend on details. Details should depend on abstractions.

Abstractions => interfaces
Details => classes

Program the interface not the implementation
Using concrete class directly creates a dependency -> difficult to modify
Invert the dependency by using an interface rather a concrete class


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
