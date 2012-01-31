#include <iostream>
#include "binary_stream.hpp"
#include <string>

struct StringBinaryOStream : public BinaryOstream {
	virtual ~StringBinaryOStream() {
	}
	virtual void save(unsigned char ch) {
		data += ch;
	}
	std::string data;
};
struct StringBinaryIStream : public BinaryIstream {
	StringBinaryIStream(const std::string& data) : offset(0),data(data)
	{
	}
	virtual ~StringBinaryIStream() {
	}
	virtual void load(unsigned char& ch) {
		ch = data[offset++];
	}
	unsigned offset;
	std::string data;
};

int main() {
	StringBinaryOStream out;
	out << 3.1415926536;
	StringBinaryIStream in(out.data);
	double pi=0.0;
	in >> pi;
	std::cout << '"' << pi << std::endl;
};
