/*
Copyright (C) 2012 André Puel

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef __BINARY_STREAM_HPP_940804189719_
#define __BINARY_STREAM_HPP_940804189719_

#include <cmath>
#include <limits>

template <typename T>
struct LittleEndian {
	LittleEndian(T t) : t(t) {}
	T t;
};
template <typename T>
struct BigEndian {
	BigEndian(T t) : t(t) {}
	T t;
};

class BinaryOstream {
public:
	virtual ~BinaryOstream() {
	}

	template <typename T>
	BinaryOstream& operator<<(const T& obj) {
		save(obj);
		return *this;
	}
	template <typename T>
	BinaryOstream& operator<<(BigEndian<T> obj) {
		save(obj);
		return *this;
	}
	template <typename T>
	BinaryOstream& operator<<(LittleEndian<T> obj) {
		save(obj);
		return *this;
	}

	template <typename T>
	void save(const T& obj);
	template <typename T>
	void save(BigEndian<T> obj);
	template <typename T>
	void save(LittleEndian<T> obj);

	BinaryOstream& operator<<(long t) {
		save(static_cast<int>(t));
		return *this;
	}
	BinaryOstream& operator<<(unsigned char t) {
		save(static_cast<char>(t));
		return *this;
	}

	void save(unsigned long long);
	void save(unsigned int);
	void save(unsigned short);
	inline void save(unsigned char c) { save(static_cast<char>(c)); }
	virtual void save(char)=0;
	void save(long long);
	void save(int);
	void save(short);
	void save(float);
	void save(double);
};

class BinaryIstream {
public:
	virtual ~BinaryIstream() {
	}

	template <typename T>
	BinaryIstream& operator>>(T& obj) {
		load(obj);
		return *this;
	}
	template <typename T>
	BinaryIstream& operator>>(BigEndian<T&> obj) {
		load(obj);
		return *this;
	}
	template <typename T>
	BinaryIstream& operator>>(LittleEndian<T&> obj) {
		load(obj);
		return *this;
	}
	template <typename T>
	void load(T& obj);
	template <typename T>
	void load(BigEndian<T&> obj);
	template <typename T>
	void load(LittleEndian<T&> obj);
	virtual void load(char& ch)=0;
	inline void load(unsigned char& ch) { load(reinterpret_cast<char&>(ch)); }
};

#endif
