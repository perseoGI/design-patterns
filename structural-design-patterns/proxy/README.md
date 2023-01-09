# Proxy Structural Pattern

Provide a surrogate or placeholder for another object to control access to it.
Proxy is an alias to an object

<img src="https://user-images.githubusercontent.com/26503843/211289290-29ac4b75-ca92-42af-a477-6a398c537dad.png" alt="drawing" width="700"/>


## Pros

- Provides a layer of indirection in which we can provide additional behaviour to the subject 
- Can hide location of the real subject
- Allow restricted access to the real subject
- Provides matching interface, allowing real subject to be replaced by a proxy easily

## Cons

- Tight coupling between the proxy and the real subject
- Adds only one new behaviour (at compile time)

## When to use?

- Whet it is not feasible to use the real object directly:
    - Remote component has to be used
    - Expensive object has to be created on demand
    - Restrict access to an object
    - Avoid manual memory management

## Implementation

- Proxy should have the same interface as that of the real object 
- Client should not distinguish between the real subject and the proxy
- One way to achieve this is to inherit the proxy from the same class that the real subject inherits from
- This allows to replace an object with proxy without significant changes
- **In C++ we can overload `*` and `->` operator without having to implement all the methods of the real subject**
- A proxy may create instance of the real subject
    - May create object on demand -> object is too expensive 
- One proxy can work with multiple subjects through an abstract interface
    - Reduces coupling between classes
    - used whet the proxy provides a common implementation for all the classes

## Proxy Types

### Virtual Proxy

Creates expensive objects on demand

### Cache Proxy

Caches expensive calls

### Remote Proxy

Simplifies client implementation, allowing calls to remote objects through network

RPC:
```
Client Process --> Remote Proxy ----------|network|----------> Stub --> Server
```

Here, client process will implemente a remote proxy which will be in charge of network calls and de/serialization
On the other hand, server will implement a Stub which is another proxy that simplifies the view to the server

### Protection Proxy

Provides access management

### Smart Proxy

Performs additional actions

Smart pointer for example, adds extra behaviour on top of the class
