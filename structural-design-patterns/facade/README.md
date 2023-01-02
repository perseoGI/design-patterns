# Facade Structural Pattern

Provide a unified interface to a set of interfaces in a subsystem.
Facade defines a higher-level interface that makes the subsystem easier to use.

## Pros

- Isolates the clients from components with complex interface
- Reduces the number of objects the client interact with
- Leads to weak coupling
- Underlying components can change without impacting the client
- Reduces compilation dependencies in large systems 
- Facade do not hide the underlying classes of the subsystem
- Clients can still use the classes if they need to
- Provide an OO interface to
    - Low level operating system functions or APIs
    - data structures, thereby reducing programming errors

## Cons

- Overuse leads to too many layers
- Performance of the system may degrade

## When to use?

- Create a simple interface to a complex system
    - This could be a default view for most clients
    - Other clients that need customization can use the underlying classes directly
- A system has evolved and gets more complex
    - Early users might want to retain their views of the system
- The application depends on low level OS APIs
    - You want to avoid coupling with a specific OS
    - You want to provide an object-oriented wrapper
- Team members with different level of experience use the system
    - you might want to provide novice or power user interfaces
- Too many dependencies between clients and the implementation classes of a subsystem

## Implementation

- Can be a function, a class or a set of classes
- Multiple facades  can be created for a system
- Each facade may provide a simplified interface for a particular functionality
- Such facades can inherit a common base class (may be abstract)
- Can further reduce the coupling between the client and the classes in the system
- Facade can be implemented as a singleton
- Facades dont encapsulate the classes of the system
- However, some facades may hide the implementation classes to reduce coupling
- Types of facades:
    - Transparent: allows direct access to the underlying classes (facade methods are optional to client)
    - Opaque: hides the underlying classes
- Facade may:
    - pass the client request to underlying classes 
    - perform additional processing
