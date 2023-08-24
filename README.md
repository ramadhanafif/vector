# Vector Library C

A library for working with vectors in C.

This library draws heavy inspiration from the [Mashpoe c-vector](https://github.com/Mashpoe/c-vector) project. However, I've taken a ground-up approach to ensure it's well-suited for Embedded-C use cases. Despite this, the end result shares similarities with Mashpoe's library.
The primary data structure remains consistent with Mashpoe c-vector, which also inspired from [antirez sds](https://github.com/antirez/sds/).
I've undertaken a complete rewrite with the specific improvement in the field of:

- CMake integration
- Static and dynamic declaration
- Configuration using header file

This library adheres to the C99 standard, while also making extensive use of the `__typeof__()` function to deduce data size. It's important to note that in C99, this function is not a standardized part of the language; rather, it is an extension found in GCC and Clang compilers. Hence, it's recommended to consider your specific compiler in this regard.
