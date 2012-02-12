Binary Stream
=============
BinaryStream is a minimalist code that performs serialization and deserialization of C++ objects.

The library can serialize integers and floating point types. The user must provide a destination for each `char`, and tell how to serialize new data types in means of already serializable data.

How to use it
-------------
The user must extend class BinaryOstream to implement the method `void save(char)`, this method is used to save each byte of the serialized data. Also the user must extend class BinaryIstream to implement the method `void load(char&)`, which is used to request bytes from the serialized data.

To make new types serializable you must implement - in a .cpp file, headers are not needed - the specialized template functions `template <> void BinaryOstream::save(const YourType&)`, and `template <> void BinaryIstream::load(YourType&)`. Inside the implementation of these, you may invoke `save`|`load` with any serializable type.

Finally, like in `std::cout` and `std::cin` you use the operators `<<` (bit-wise shift left) and `>>` (bitwise shift right) respectively to save and load objects.

Primitive Types Representation
------------------------------
### Integer
Unsigned integral data types are saved as a string of bits with the length of the data type. `short` occupies 2 bytes, `int` and `long` occupies 4 bytes, and `long long` occupies 8 bytes. Signed data types use two`s complement representation. By default, little endian is used.

This way, if a code serializes some data type casting a integer to `char*`, the final output will be the same. 

### Floating pointer types
The floating point representation follow the [IEEE 754 Standard](http://en.wikipedia.org/wiki/Floating_point#Internal_representation), using 4 bytes for `float` and 8 bytes for `double`.

Endianess
---------
There are two template classes called `BigEndian<T>` and `LittleEndian<T>` that you may use to force the endianess of loaded or saved primitive data. These classes just receive a T value at construction and hold it. It won't change the held type in anyway, it just a way to the serializer know how to threat the data held.

Cross platform
-------------
The protocol that save primitive types doesn't rely on machine internal representation, it uses only mathematical operations that are cross platform. Floating pointer serialization just needs that the functions `ldexp` and `frexp` are available.

In future releases, it will be possible to tell - using a macro definition - the library that your CPU is not weird and that its safe to save primitive data casting to `char*` 

Future Work
-----------
* Class to ease serializing array data, `ArrayData<T>(T*, unsigned size)`
* Serializing STL containers data
* Pointer serialization (if you save the same pointed data twice, it is saved only once)
* Polymorphic serialization (saving and loading the exact object your pointer is using, despite the variable type)
