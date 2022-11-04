# Object Pool Creational Pattern

Variation of Factory Method creational pattern & not an official pattern.

Allows to use cached instances of objects instead of creating new objects each time the factory is called.

Improve performance & memory use by reusing objects from a fixed pool instead of allocating & freeing them repetitively.

## Pros

## Cons


## When to use?

- Application needs to create and destroy tons of objects and that is a performance issue (tends to fragment the heap)

## Implementation

- Object Pool maintains a list of SharedObject instances.
- SharedObject instances are not created by the clients directly, instead, they use the object pool.
- Objects are constructed when:
    - The program starts
    - The pool is empty
    - An existing SharedObject is not available
        - The Object Pool can be grown automatically
- Object Pool can be implemented as a Singleton or Monostate
- Clients acquire a SharedObject instance by invoking a factory method in the pool
- This object gets removed from the pool or marked as "used"
- The client may manually return a SharedObject to the pool or it may be done automatically
- The pooled object instance can be reset
    - Before giving it to the client
    - After it is returned to the pool
- The Object Pool is responsible for deleting the pooled instances (usually at the end of program)
- To avoid tight coupling with concrete pooled objects, Object Pool can use a factory to instantiate them
