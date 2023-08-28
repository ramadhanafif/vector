# Vector Library C

A library for working with vectors in C. With the specific improvement:

- Follows C99, makes it suitable to nearly most of C projects!
- CMake integration: just put `add_subdirectory(vector)` and `target_link_libraries(executable PUBLIC vector)` to your top level CMakeLists.txt!
- Proper unit-testing and memory safety checking with [Valgrind](valgrind.org) and [Address Sanitizer](https://github.com/google/sanitizers/wiki/AddressSanitizer)!
- Support for
  - dynamic memory storage
  - static memory storage for Embedded Systems (Work-in-progress)
- Configuration using header file and CMake options (Work-in-progress)

This library draws heavy inspiration from the [Mashpoe c-vector](https://github.com/Mashpoe/c-vector) project. However, I've taken a ground-up approach to ensure it's well-suited for general AND embedded use cases.
The primary data structure remains consistent with Mashpoe c-vector, which also inspired from [antirez sds](https://github.com/antirez/sds/).

This library adheres to the C99 standard, while also making extensive use of the `__typeof__()` function to deduce data size. It's important to note that in C99, this function is not a standardized part of the language; rather, it is an extension found in GCC and Clang compilers. Hence, it's recommended to consider your specific compiler in this regard.

# Tests

Vector uses [ThrowTheSwitch Unity Test](https://github.com/ThrowTheSwitch/Unity) as unit testing framework. Included as a git submodule in the external directory
To run tests by yourself:

- Ensure to install the pre-requisite:
  - address sanitizer library (libasan)
  - undefined behaviour sanitizer library (libubsan)
  - CMake
  - compiler (GCC or Clang) that supports typeof method
- Clone this repo with the submodules `git clone https://github.com/ramadhanafif/vector --recursive`
- Inside the Vector directory, configure cmake with the command `cmake -Bbuild`
- Run the test with `cmake --build build -t runtest`
