CXXFLAGS=-O0 -g2 -std=c++0x
CXX=g++

all: tests

tests: primitives.o test_runner.o
	${CXX} ${CXXFLAGS} $^ -o $@

primitives.o: binary_stream.hpp string_binary_stream.hpp test_runner.hpp

clean:
	rm *.o tests
