# Prototype Creational Pattern

Specify the kinds of objects to create using a prototypical instance, and
create new objects by copying this prototype

## Pros

- As it behaves as a factory, it has all the pros a factory has
- Concrete classes are hidden from the clients -> loose coupling
- Products can be added or removed at runtime -> useful for languages without reflection (C++)
- New objects can be specified by varying values -> reduces number of classes

## Cons

- Each class must support `clone()` operation -> difficult to add if the classes already exist
    - All classes must inherit from base class
- Difficult to implement when class internals contain members that do not support copying (streams, threads, etc)

## When to use?

- Achieve loose coupling -> reduce dependency on concrete classes
- Avoid parallel hierarchy of factories by creating a one factory that return clones of existing objects
- A class have few variations in their instances state
    - Instead of creating different classes, create properties in the class
- Dynamically specify new objects in the application

## Implementation

- The classes whose objects need to be cloned inherit from a common base class
- This class provides an overridable method called clone
- This method can be overridden by the sub-classes to create a copy of themselves
- The client can then call this method to create copies/clones of existing objects
- After cloning, the client may change some state of the cloned objects
- Consequently, the classes may have to provide initialize/setter methods

- Clone method in C++ behaves like a virtual copy constructor


## Types of copying
### Shallow Copy

- A copy is created by copying the state of the object
- Programming languages support this feature through cloning/copy constructor
- Default implementation of these methods will copy the references in the object instead of coping the actual data

#### C++

- Primitive types are copied
- References cannot be copied, they are just aliases
- Pointers are copied (the address, not the data)

A class with a pointer (resource) (acquired in constructor and released in destructor) has ownership semantics.
A class with ownership semantics must implement the **Rule Of Five!**:

- Copy Constructor
- Copy Assignment
- Move Constructor
- Move Assignment
- Destructor


### Deep copy

- The state is copied but references are copied differently
- References are not copied, instead the objects they refer to are copied
- Usually has to be implemented manually


## Issues with copy constructor C++

Most of the times it is not a good idea to use it (game.cpp)

1. Needs a concrete object
2. Needs a type class
3. Needs to include concrete classes in the client
4. If we dont know the concrete type of the object to clone to, a `typeid` or `dynamic_cast` should be used and this is considered a code smell


Virtual constructor: copy constructor which does not need to know the type of the object being copied -> C++ does not provide such thing.


## Prototype Manager

- Class that manages the state of the current copies
- Responsible for storing the prototypes in the application
- When the application requieres an instance, it should request it to the Prototype Manager
- It will return a clone of an existing instances
- Application can register / deregister classes at runtime

## Alternative implementation

- Serialization can be used for cloning
- Does not mandate implementation of any interface
- Always creates a deep copy
- Useful when the prototype is required at some late point -> write to disk (inefficient)
