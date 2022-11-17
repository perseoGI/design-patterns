# Builder Creational Pattern

- Construction of complex object cat be simplified through a builder
- Builder encapsulates the construction logic in a different class
- This allows creation of different representations of the object
- The object is constructed step-by-step, other creational patterns construct objects in one shot

Separate the construction of a complex object from its representation so that
the same construction process can create different representations

## Pros

- Hides internal representation and structure of the product
- Hides how the product gets assembled
- To get a new product with a different internal representation, you just define a new builder
- Separation between code that constructs the object and the one that represents it
- Gives more control over the construction process of the object

## Cons

- May increase the overall complexity of the code -> depends of what kind of object is being constructed

## When to use?

- Get rid of a class with multiple constructors
- Get rid of delegating constructors (call constructor on initializer list from another constructor)
- Separate the algorithm of the object construction
- Create different representations of some product

## Implementation

- The construction process of an object is directed by a class called director
- The director use builder class to assembly an object in steps
- To create different kinds of objects, the director will use different builders
- All the builder classes may inherit from a common base class
- The base class will have the appropriate interface to allow creation of different kind of objects in steps

## Method Chaining / Fluent Interface / Cascade

Each method of a class returns instance of current object, and that object is used to invoke next method in the chain.

Reduce syntactical noise -> more readable output.

Most of the implementations of the Builder Pattern uses the Fluent Interface.

```cpp
Builder builder;
Object obj {builder.methodA().methodB().methodC().methodD().build()};
```

## Alternative Implementation

- Modern implementation of builder do not use Director class
- The builde can be a nested class of the product that it builds
- Simplifies the code, especially whet the builder constructs the same object (albeit with different states)
