# Adapter Structural Pattern

Convert the interface of a class into another interface clients expect. Adapter
lets classes work together that could not otherwise because of incompatible interfaces.

Used for interface inversion: 
- Convert incompatible interfaces into compatible ones
- Adapt/check input parameters and return values to match both interfaces

## Adapter Variations
### Object Adapter

<img src="https://user-images.githubusercontent.com/26503843/208723419-488b698e-0f59-429c-921d-cdd4d504aa94.png" alt="drawing" width="700"/>

- Client can only make a concrete request
- The library/class which can't be modified by client do not expose that method the way client must call it
- Create a Adapter class which inherits from Target interface
- Adapter compose the Adaptee class

### Class Adapter

<img src="https://user-images.githubusercontent.com/26503843/208723494-2550c434-43ed-4b3b-bb84-7744be4cfbe0.png" alt="drawing" width="700"/>

- Adapter inherit from Target so that it inherit the client interface
- Adapter inherit from Adaptee so that it inherit its implementation

## Pros

### Object Adapter

- One object adapter can work with multiple classes (even subclasses of adaptee) -> allow work with many classes in a hierarchy 
- Can always adapt to an existing class

### Class Adapter

- Method calls are direct as they are inherited (no pointer indirection)
- Can override adaptee's behaviour

## Cons

### Object Adapter

- Cannot override adaptee's behaviour
- Methods are invoked through pointer indirection

### Class Adapter

- Won't work if the adaptee is final or sealed class
- Uses multiple class inheritance (may not be possible in all languages)
- Won't work with subclasses of adaptees

## When to use?

- Want to use an existing components with an incompatible interface
- Need to use classes from an existing hierarchy but they have incompatible interface (object adapter)
- Need to reuse an existing class with incompatible interface but want to modify some behaviour (class adapter)

## Implementation

- Can be implemented either through composition or inheritance
- Via composition:
    - Adapter composes the adaptee and calls its methods through a reference/pointer indirection
- Via inheritance:
    - Adapter inherits from adaptee and calls its methods directly

