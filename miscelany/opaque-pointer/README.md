# Opaque pointer

Explanation on [Wikipedia](https://en.wikipedia.org/wiki/Opaque_pointer)

This technique allows two main things:

1. Obfuscate implementation details for a class / structure on a library
2. Improve compilation performance:
  - Changes on implementation files wont affect header files so there is no need to recompile every file which includes the header
  - Header file will only need to include files needed for the class interface (and not for the class implementation) avoiding parse the code in all the files including header



