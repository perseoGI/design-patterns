# Abstract Factory Creational Pattern

Provide an interface for creating families of related or dependent object
without specifying their concrete classes

The difference between Factory Method and Abstract Factory is that whereas both
create instances of classes, Abstract Factory returns instances of specific
family or set.

Objects in a family or set are design to work together and they depend between each other.

## Pros

- Promotes loose coupling
- To support more configurations in the future:
  - Add the classes for a new set
  - add corresponding factory class
- Enforces consistency among products as the application can get instances of
  classes only from one set at a time

## Cons

- Adding new products is difficult
- Entails modification of the abstract factory interface which in turn will force child classes to change
- Adding a new configuration causes class explosion

# Factory Method vs Abstract Factory

| Factory Method                                                        | Abstract Factory                                                                                         |
| --------------------------------------------------------------------- | -------------------------------------------------------------------------------------------------------- |
| Manages the creation of object without depending on its concrete type | Manages creation of related families or interdependent classes without depending on their concrete types |
| Subclasses manage the creation of the concrete type                   | Creation depends on the type of factory used                                                             |
| Easy expand factory class to support new products                     | Difficult to extend the factories to support new products                                                |
| Many factories can be used simultaneously                             | Only one factory is used at a time                                                                       |

## When to use?

- Provide instances to clients without exposing concrete classes
- Configure a system with one of multiple product configurations
- Enforce use classes only from one family at a time

## Implementation

- An Abstract Factory defines the interface for creating different products (factory methods)
- Factories are added for each context (family or set)
- All factories inherit from the abstract factory
- Each factory will create instances of classes for the corresponding context
- Only one factory will be used in the whole application through the base abstract factory reference
- Factories can be implemented as a singleton / monostate
