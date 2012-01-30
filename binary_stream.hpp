#ifndef __BINARY_STREAM_HPP_940804189719_
#define __BINARY_STREAM_HPP_940804189719_

class BinaryOstream {
public:
	virtual ~BinaryOstream() {
	}
	virtual void savechar(unsigned char ch)=0;

	template <typename T>
	BinaryOstream& operator<<(T obj) {
		save(obj);
		return *this;
	}

	template <typename T>
	void save(T obj);
};

class BinaryIstream {
public:
	virtual ~BinaryIstream() {
	}
	virtual void loadchar(unsigned char& ch)=0;

	template <typename T>
	BinaryIstream& operator>>(T& obj) {
		load(obj);
		return *this;
	}

	template <typename T>
	void load(T& obj);
};

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

template<>
void BinaryOstream::save(unsigned char t) {
	savechar(t);
}
template<>
void BinaryIstream::load(unsigned char& t) {
	loadchar(t);
}
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
	load(buf); t.t = buf<<56;
	load(buf); t.t = buf<<48;
	load(buf); t.t = buf<<40;
	load(buf); t.t = buf<<32;
	load(buf); t.t = buf<<24;
	load(buf); t.t += buf<<16;
	load(buf); t.t += buf<<8;
	load(buf); t.t += buf;
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
void BinaryOstream::save(LittleEndian<unsigned int> t ) {
	save( (unsigned char)((t.t) & 0xFF) );
	save( (unsigned char)((t.t>>8) & 0xFF) );
	save( (unsigned char)((t.t>>16) & 0xFF) );
	save( (unsigned char)((t.t>>24) & 0xFF) );
};
template <>
void BinaryIstream::load(LittleEndian<unsigned int&> t) {
	unsigned char buf;
	load(buf); t = buf;
	load(buf); t += buf<<8;
	load(buf); t += buf<<16;
	load(buf); t += buf<<24;
}
template <>
void BinaryOstream::save(LittleEndian<unsigned short> t) {
	save( (unsigned char)((t) & 0xFF) );
	save( (unsigned char)((t>>8) & 0xFF) );
}
template <>
void BinaryIstream::load(LittleEndian<unsigned short&> t) {
	unsigned char buf;
	load(buf); t = buf;
	load(buf); t += buf<<8;
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
	if( buffer <= Middle ) { \
		t.t = buffer; \
		return; \
	} \
	t = buffer-1-Max; \
	return; \
}

__STREAM_SIGNED(BigEndian,long long,0xFFFFFFFFFFFFFFFF,0x7FFFFFFFFFFFFFFF)
__STREAM_SIGNED(LittleEndian,long long,0xFFFFFFFFFFFFFFFF,0x7FFFFFFFFFFFFFFF)
__STREAM_SIGNED(BigEndian,int,0xFFFFFFFF,0x7FFFFFFF)
__STREAM_SIGNED(LittleEndian,int,0xFFFFFFFF,0x7FFFFFFF)
__STREAM_SIGNED(BigEndian,short,0xFFFF,0x7FFF)
__STREAM_SIGNED(LittleEndian,short,0xFFFF,0x7FFF)

template <> void BinaryOstream::save(unsigned long long t) { save(BigEndian<unsigned long long>(t)); }
template <> void BinaryIstream::load(unsigned long long& t) { save(BigEndian<unsigned long long&>(t)); }
template <> void BinaryOstream::save(long long t) { save(BigEndian<long long>(t)); }
template <> void BinaryIstream::load(long long& t) { save(BigEndian<long long&>(t)); }
template <> void BinaryOstream::save(unsigned int t) { save(BigEndian<unsigned int>(t)); }
template <> void BinaryIstream::load(unsigned int& t) { save(BigEndian<unsigned int&>(t)); }
template <> void BinaryOstream::save(int t) { save(BigEndian<int>(t)); }
template <> void BinaryIstream::load(int& t) { save(BigEndian<int&>(t)); }
template <> void BinaryOstream::save(unsigned short t) { save(BigEndian<unsigned short>(t)); }
template <> void BinaryIstream::load(unsigned short& t) { save(BigEndian<unsigned short&>(t)); }
template <> void BinaryOstream::save(short t) { save(BigEndian<short>(t)); }
template <> void BinaryIstream::load(short& t) { save(BigEndian<short&>(t)); }

#endif
