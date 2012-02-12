/*
Copyright (C) 2012 André Puel

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef __STRING_BINARY_STREAM_HPP_4901249801481_
#define __STRING_BINARY_STREAM_HPP_4901249801481_

#include "binary_stream.hpp"

struct StringBinaryOStream : public BinaryOstream {
	virtual ~StringBinaryOStream() {
	}
	virtual void save(char ch) {
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
	virtual void load(char& ch) {
		ch = data[offset++];
	}
	unsigned offset;
	std::string data;
};

#endif
