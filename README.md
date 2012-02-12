# Binary Stream, a minimalistic compact serializer for C++
## Overview
BinaryStream is a minimalistic code that performs serialization and deserialization of C++ objects.

The library can serialize integers and floating point types. The user must provide a destination for each `char`, and tell how to serialize new data types in means of already serializable data.

## How to use it
The user must extend class BinaryOstream to implement the method `void save(char)`, this method is used to save each byte of the serialized data. Also the user must extend class BinaryIstream to implement the method `void load(char&)`, which is used to request bytes from the serialized data.

To make new types serializable you must implement - in a .cpp file, no need of headers - the specialized template functions `template <> void BinaryOstream::save(const YourType&)`, and `template <> void BinaryIstream::load(YourType&)`.

Finally, like in std::cout and std::cin you use the operators << (bitwise shift left) and >> (bitwise shift right) respectively to save and load objects.
