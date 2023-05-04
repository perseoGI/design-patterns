# Decorator Structural Pattern

Attach additional responsibilities to an object dynamically.
Decorators provide a flexible alternative to subclassing for extending functionality.

Features are added at runtime.

Decorator are wrapper class that internally uses the component which is wrapping.

## Pros

## Cons

## When to use?

## Implementation

- A decorator's interface must conform to the interface of the object it decorates
    - All decorators must inherit from a common base class
- Abstract decorator is not required if only one responsibility has to be added
    - Decorator can itself forward the calls to the object
- Abstract decorator & its base class should be lightweight
    - Should focus on defining interface, not storing data
    - Avoid adding concrete implementation as not all subclasses may require it
    - These objects are part of every decorator and will make the decorators bulky to use
- Decorator changes the skin of the object. An alternative is to change the guts (through Strategy Pattern)
