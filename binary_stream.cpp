/*
Copyright (C) 2012 André Puel

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <binary_stream.hpp>

template <>
void BinaryOstream::save(BigEndian<unsigned long long> t ) {
	save( (unsigned char)((t.t>>56) & 0xFF) );
	save( (unsigned char)((t.t>>48) & 0xFF) );
	save( (unsigned char)((t.t>>40) & 0xFF) );
	save( (unsigned char)((t.t>>32) & 0xFF) );
	save( (unsigned char)((t.t>>24) & 0xFF) );
	save( (unsigned char)((t.t>>16) & 0xFF) );
	save( (unsigned char)((t.t>>8) & 0xFF) );
	save( (unsigned char)((t.t) & 0xFF) );
}
template <>
void BinaryIstream::load(BigEndian<unsigned long long&> t) {
	unsigned char buf;
	load(buf); t.t = static_cast<unsigned long long>(buf)<<56;
	load(buf); t.t += static_cast<unsigned long long>(buf)<<48;
	load(buf); t.t += static_cast<unsigned long long>(buf)<<40;
	load(buf); t.t += static_cast<unsigned long long>(buf)<<32;
	load(buf); t.t += static_cast<unsigned long long>(buf)<<24;
	load(buf); t.t += static_cast<unsigned long long>(buf)<<16;
	load(buf); t.t += static_cast<unsigned long long>(buf)<<8;
	load(buf); t.t += static_cast<unsigned long long>(buf);
}
template <>
void BinaryOstream::save(BigEndian<unsigned int> t ) {
	save( (unsigned char)((t.t>>24) & 0xFF) );
	save( (unsigned char)((t.t>>16) & 0xFF) );
	save( (unsigned char)((t.t>>8) & 0xFF) );
	save( (unsigned char)((t.t) & 0xFF) );
};
template <>
void BinaryIstream::load(BigEndian<unsigned int&> t) {
	unsigned char buf;
	load(buf); t.t = buf<<24;
	load(buf); t.t += buf<<16;
	load(buf); t.t += buf<<8;
	load(buf); t.t += buf;
}
template <>
void BinaryOstream::save(BigEndian<unsigned short> t) {
	save( (unsigned char)((t.t>>8) & 0xFF) );
	save( (unsigned char)((t.t) & 0xFF) );
}
template <>
void BinaryIstream::load(BigEndian<unsigned short&> t) {
	unsigned char buf;
	load(buf); t.t = buf<<8;
	load(buf); t.t += buf;
}

template <>
void BinaryOstream::save(LittleEndian<unsigned long long> t ) {
	save( (unsigned char)((t.t) & 0xFF) );
	save( (unsigned char)((t.t>>8) & 0xFF) );
	save( (unsigned char)((t.t>>16) & 0xFF) );
	save( (unsigned char)((t.t>>24) & 0xFF) );
	save( (unsigned char)((t.t>>32) & 0xFF) );
	save( (unsigned char)((t.t>>40) & 0xFF) );
	save( (unsigned char)((t.t>>48) & 0xFF) );
	save( (unsigned char)((t.t>>56) & 0xFF) );
};
template <>
void BinaryIstream::load(LittleEndian<unsigned long long&> t) {
	unsigned char buf;
	load(buf); t.t = static_cast<unsigned long long>(buf);
	load(buf); t.t += static_cast<unsigned long long>(buf)<<8;
	load(buf); t.t += static_cast<unsigned long long>(buf)<<16;
	load(buf); t.t += static_cast<unsigned long long>(buf)<<24;
	load(buf); t.t += static_cast<unsigned long long>(buf)<<32;
	load(buf); t.t += static_cast<unsigned long long>(buf)<<40;
	load(buf); t.t += static_cast<unsigned long long>(buf)<<48;
	load(buf); t.t += static_cast<unsigned long long>(buf)<<56;
}
template <>
void BinaryOstream::save(LittleEndian<unsigned int> t ) {
	save( (unsigned char)((t.t) & 0xFF) );
	save( (unsigned char)((t.t>>8) & 0xFF) );
	save( (unsigned char)((t.t>>16) & 0xFF) );
	save( (unsigned char)((t.t>>24) & 0xFF) );
};
template <>
void BinaryIstream::load(LittleEndian<unsigned int&> t) {
	unsigned char buf;
	load(buf); t.t = buf;
	load(buf); t.t += buf<<8;
	load(buf); t.t += buf<<16;
	load(buf); t.t += buf<<24;
}
template <>
void BinaryOstream::save(LittleEndian<unsigned short> t) {
	save( (unsigned char)((t.t) & 0xFF) );
	save( (unsigned char)((t.t>>8) & 0xFF) );
}
template <>
void BinaryIstream::load(LittleEndian<unsigned short&> t) {
	unsigned char buf;
	load(buf); t.t = buf;
	load(buf); t.t += buf<<8;
}

#define __STREAM_SIGNED(Endian,Type,Max,Middle) template <> \
void BinaryOstream::save(Endian<Type> t) { \
	if( t.t > 0 ) { \
		save( Endian<unsigned Type>(static_cast<unsigned Type>(t.t)) ); \
		return; \
	} \
	unsigned Type value = Max;\
	value -= -t.t;\
	value += 1;\
	save( Endian<unsigned Type>(value) );\
} \
\
template<> \
void BinaryIstream::load(Endian<Type&> t) { \
	unsigned Type buffer; \
	load(Endian<unsigned Type&>(buffer)); \
	if( buffer <= Middle ) { \
		t.t = buffer; \
		return; \
	} \
	t.t = buffer-1-Max; \
	return; \
}

__STREAM_SIGNED(BigEndian,long long,0xFFFFFFFFFFFFFFFF,0x7FFFFFFFFFFFFFFF)
__STREAM_SIGNED(LittleEndian,long long,0xFFFFFFFFFFFFFFFF,0x7FFFFFFFFFFFFFFF)
__STREAM_SIGNED(BigEndian,int,0xFFFFFFFF,0x7FFFFFFF)
__STREAM_SIGNED(LittleEndian,int,0xFFFFFFFF,0x7FFFFFFF)
__STREAM_SIGNED(BigEndian,short,0xFFFF,0x7FFF)
__STREAM_SIGNED(LittleEndian,short,0xFFFF,0x7FFF)

void BinaryOstream::save(unsigned long long t) { save(LittleEndian<unsigned long long>(t)); }
template <> void BinaryIstream::load(unsigned long long& t) { load(LittleEndian<unsigned long long&>(t)); }
void BinaryOstream::save(long long t) { save(LittleEndian<long long>(t)); }
template <> void BinaryIstream::load(long long& t) { load(LittleEndian<long long&>(t)); }
void BinaryOstream::save(unsigned int t) { save(LittleEndian<unsigned int>(t)); }
template <> void BinaryIstream::load(unsigned int& t) { load(LittleEndian<unsigned int&>(t)); }
void BinaryOstream::save(int t) { save(LittleEndian<int>(t)); }
template <> void BinaryIstream::load(int& t) { load(LittleEndian<int&>(t)); }
void BinaryOstream::save(unsigned short t) { save(LittleEndian<unsigned short>(t)); }
template <> void BinaryIstream::load(unsigned short& t) { load(LittleEndian<unsigned short&>(t)); }
void BinaryOstream::save(short t) { save(LittleEndian<short>(t)); }
template <> void BinaryIstream::load(short& t) { load(LittleEndian<short&>(t)); }

static unsigned int floatToUnsigned(float t) {
	unsigned int data;
	if( t == 0 ) {
		data = 0;
	} else if( isnan(t) ) {
		data = 2143289344;
	} else if( t == std::numeric_limits<float>::infinity() ) {
		data = 2139095040;
	} else if( t == -std::numeric_limits<float>::infinity() ) {
		data = 4286578688;
	} else {
		bool minus=false;
		if( t < 0 ) { minus=true;t*=-1; }
		int exponent;
		float fraction = frexp(t,&exponent);

		data = ((unsigned int)(fraction*(1<<24))&0x7FFFFF);
		data |= (exponent+126)<<23;
		if( minus ) { data |= 0x80000000; }
	}
	return data;
}
static void unsignedToFloat(unsigned int data, float& result) {
	if( data == 0 ) {
		result = 0.0;
	} else if( data == 2143289344 ) {
		result = std::numeric_limits<float>::quiet_NaN();
	} else if( data == 2139095040 ) {
		result = std::numeric_limits<float>::infinity();
	} else if( data == 4286578688 ) {
		result = -std::numeric_limits<float>::infinity();
	} else {
		bool minus = data>>31;
		int exponent = ((data>>23)&0xFF)-126;
		float fraction = double((data&0x7FFFFF)|0x800000)/(1<<24);
		if( minus ) fraction *= -1.0;
		result = ldexp(fraction,exponent);
	}
}
template <>
void BinaryOstream::save( LittleEndian<float> t ) {
	save( LittleEndian<unsigned int>(floatToUnsigned(t.t)) );
}
template <>
void BinaryOstream::save( BigEndian<float> t ) {
	save( BigEndian<unsigned int>(floatToUnsigned(t.t)) );
}
template <>
void BinaryIstream::load( LittleEndian<float&> t ) {
	unsigned int buffer;
	load( LittleEndian<unsigned int&>(buffer) );
	unsignedToFloat(buffer,t.t);
}
template <>
void BinaryIstream::load( BigEndian<float&> t ) {
	unsigned int buffer;
	load( BigEndian<unsigned int&>(buffer) );
	unsignedToFloat(buffer,t.t);
}

static unsigned long long doubleToUnsigned(double t) {
	unsigned long long data;
	if( t == 0 ) {
		data = 0;
	} else if( isnan(t) ) {
		data = 9221120237041090560ul; 
	} else if( t == std::numeric_limits<double>::infinity() ) {
		data = 9218868437227405312ul;
	} else if( t == -std::numeric_limits<double>::infinity() ) {
		data = 18442240474082181120ul;
	} else {
		bool minus=false;
		if( t < 0 ) { minus=true;t*=-1; };
		int exponent;
		double fraction = frexp(t,&exponent);
		
		data = ((unsigned long long)(fraction*(1ull<<53)))&0xFFFFFFFFFFFFF;
		data |= (unsigned long long)(exponent+1022)<<52;
		if( minus ) { data |= 0x8000000000000000; }
	}

	return data;
}
static void unsignedToDouble(unsigned long long data, double& result) {
	if( data == 0 ) {
		result = 0.0;
	} else if( data == 9221120237041090560ul ) {
		result = std::numeric_limits<double>::quiet_NaN();
	} else if( data == 9218868437227405312ul ) {
		result = std::numeric_limits<double>::infinity();
	} else if( data == 18442240474082181120ul ) {
		result = -std::numeric_limits<double>::infinity();
	} else {
		bool minus = data>>63;
		int exponent = ((data>>52)&0x7FF)-1022;
		double fraction = double((data&0xFFFFFFFFFFFFF)|0x10000000000000)/(1ull<<53);
		if( minus ) fraction *= -1.0;
		result = ldexp(fraction,exponent);
	}
}

template <>
void BinaryOstream::save( LittleEndian<double> t ) {
	save( LittleEndian<unsigned long long>(doubleToUnsigned(t.t)) );
}
template <>
void BinaryOstream::save( BigEndian<double> t ) {
	save( BigEndian<unsigned long long>(doubleToUnsigned(t.t)) );
}
template <>
void BinaryIstream::load( LittleEndian<double&> t ) {
	unsigned long long buffer;
	load( LittleEndian<unsigned long long&>(buffer) );
	unsignedToDouble(buffer,t.t);
}
template <>
void BinaryIstream::load( BigEndian<double&> t ) {
	unsigned long long buffer;
	load( BigEndian<unsigned long long&>(buffer) );
	unsignedToDouble(buffer,t.t);
}

void BinaryOstream::save( float t ) { save( LittleEndian<float>(t) ); }
void BinaryOstream::save( double t ) { save( LittleEndian<double>(t) ); }
template <> void BinaryIstream::load( float& t ) { load( LittleEndian<float&>(t) ); }
template <> void BinaryIstream::load( double& t ) { load( LittleEndian<double&>(t) ); }

