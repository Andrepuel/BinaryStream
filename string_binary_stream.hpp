#ifndef __STRING_BINARY_STREAM_HPP_4901249801481_
#define __STRING_BINARY_STREAM_HPP_4901249801481_

#include "binary_stream.hpp"

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

#endif
