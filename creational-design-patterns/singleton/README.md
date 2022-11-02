# Singleton Creational Pattern

Ensure a class only has one instance, and provide a global point of access to it.

## Pros

- Complete control of instantiation process
- Can allow multiple (but limited) instances -> multiton
- Better than a global variable. Just not a single variable but an object which has the full control on all its methods
- Can be subclassed

## Cons

- Used directly through the name of the class -> difficult to test, mock
- DCLP on multithreading applications is defective
- Lazy instance destruction is complex

## When to use?

- When only one instance should be used
    - Multiple instances cause data corruption
    - Managing global/shared state
    - Multiple instances are not required

## Implementation

- Class is made responsible for its own instance
- Intercepts the call for construction and returns a single instance
- Same instance is returned every time
- Direct constructor is disabled

## Types of singleton

### Eager instance implementation

Instance is created by the time the program loads

```cpp
class Logger {
    FILE *pStream;
    Logger(){
        pStream = fopen("log.txt", "w");
    }

    inline static Logger m_instance;       // eager instance

public:
    Logger(const Logger&) = delete; // delete copy constructor
    Logger &operator= (const Logger &) = delete; // delete assignment operator

    Logger &getInstance(){          // Only method to access instance
        return m_instance;
    }

    ~Logger() = default;
    void log(const char *message) {
        fprintf(pStream"%s", message);
    }

};
```

### Lazy instance implementation

Instance is created by the time `getInstance` method is first called.
inline static (c++ v17) allow declare static class variables in class declaration

See lazy-instance.cpp.

Secure deleting a singleton:

```cpp
// With a raw pointer

Logger::Logger(){
    m_pStream = fopen("log.txt", "w");
    atexit([](){
        fclose(m_pStream);
    });
}

// Or see Deleter on example
```

## Singleton in multithreading

It is possible that two threads reach if(nullptr) at the same time, creating multiple instances of a singleton.

Prevent it with a mutex
Lock mutex on getInstance method and rest of thread unsafe methods

### DCLP

See DCLP.md

### Mayer's Singleton

Prevent DCLP thread unsafe problems by declaring a static local variable inside the `getInstance` method

From C++11, static construction is thread safe.
This avoid using heap and having to create a destructor.

```cpp
Instance & Instance::getInstance(){
    static Instance insntance;
    return instance;
}
```

### `std::call_once`

Since C++11 `call_once` was introduced to allow a thread safe one time code execution

Applied to the singleton:

```cpp
std::once_flag flag;

Instance & Instance::getInstance(){
    std::call_once(flag, [](){m_instance{new Instance{}};});
    return *m_instance;
}
```

Before C++11:

- POSIX: `pthread_once`
- Windows: `InitOnceExecuteOnce`

## Which prefer?

- If possible, always use eager instances.
- If runtime data is needed to construct the instance, use lazy instance, preferable Mayer's implementation.
- If heap is needed (?) use a smart unique pointer or raw pointer.
- Always prefer Mayer's implementation (local static variables) rather than `std::call_once` due to performance.

## Templating a Singleton (CRTP)

It is possible thanks to the Curiously Recurring Template Pattern (CRTP)

See base-template-singleton.cpp.

CRTP is a C++ idiom in which a class X derives from a class template instantiation using X itself as a template argument.

```cpp
class Derived : public Base<Derived>{};
```

## Singleton vs Monostate

| Singleton                                                                       | Monostate                                                            |
| ------------------------------------------------------------------------------- | -------------------------------------------------------------------- |
| Enforces singular instance through structure                                    | Enforces singular instance through behaviour                         |
| Only one instance can exist                                                     | Class may or may not be instantiated (depends on the implementation) |
| Support lazy instantiation                                                      | No support for lazy instantiation                                    |
| Requieres static getInstance method                                             | All attributes ares static (methods may be static)                   |
| Can support inheritance & polymorphism                                          | Static methods cannot be overridden                                  |
| Existing classes can be made singletons                                         | Difficult to migrate a existing class to monostate                   |
| Flexible (can be modified to create multiple<br> instances => multiton pattern) | Inflexible                                                           |


## Disadvantages of Singleton pattern

- Using a singleton class, its name is used directly, violating Dependency Inversion Principle -> program the interface, not the implementation
- Difficult to replace this class with other class
- Difficult to unit test / mock

There are some approach which make it easy to unit test a singleton class, see singleton-issue.cpp.


# Multiton / Singleton Registry

See `multiton.cpp`, `multiton-lazy-dynamic.cpp` and `multiton-lazy-mayers.cpp`.

A multiton could be think as a generalization of the singleton pattern, which
allows a controlled creation of multiple instances, managed through the use of
a map:

`instances: Map<key, Intance>`


