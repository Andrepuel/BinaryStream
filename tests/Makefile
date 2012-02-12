CXXFLAGS=-O0 -g2 -std=c++0x -I..
CXX=g++

all: tests

tests: primitives.o test_runner.o binary_stream.o
	${CXX} ${CXXFLAGS} $^ -o $@

primitives.o: ../binary_stream.hpp string_binary_stream.hpp test_runner.hpp

binary_stream.o: ../binary_stream.cpp
	${CXX} ${CXXFLAGS} -c $^ -o $@

clean:
	rm *.o tests
