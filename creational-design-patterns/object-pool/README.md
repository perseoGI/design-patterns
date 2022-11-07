# Object Pool Creational Pattern

Variation of Factory Method creational pattern & not an official pattern.

Allows to use cached instances of objects instead of creating new objects each time the factory is called.

Improve performance & memory use by reusing objects from a fixed pool instead of allocating & freeing them repetitively.

## Pros

- Reduces coupling with concrete classes
- Behaves like _operator new_, but is more flexible
- Caching existing instances may improves performance
- Reduces overhead of heap allocation & deallocation
- Reduces heap fragmentation

## Cons

- Memory may be wasted on unused pooled objects
- Pooled objects may remain in memory until the end of the program
- Object that are acquired from the pool must be reset prior to their use
    - If the pool is the one to reset the state, it may expose implementation details of the objects
- Clients have to ensure that an unused object is returned to the pool
- ObjectPool class may get tightly coupled with the classes of the pooled objects
    - May force modifying existing objects to support allocation techniques 

## When to use?

- Application needs to create and destroy tons of objects and that is a performance issue (tends to fragment the heap)
- Objects are expensive to create from scratch

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
