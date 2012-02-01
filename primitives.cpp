#include <iostream>
#include <fstream>
#include "test_runner.hpp"
#include "string_binary_stream.hpp"

BEGIN_TEST_SUITE(primitives);

TEST_CASE( int ) {
	StringBinaryOStream out;
	out << 13 << 975u << -134 << ((int)-2147483648) << 4294967295u << 0u << -1;
	out << BigEndian<int>(-1) << LittleEndian<unsigned int>(124) << LittleEndian<int>(9785) << BigEndian<unsigned int>(2101);

	int a,c,d,g,h,j;
       	unsigned int b,e,f,i,k;

	StringBinaryIStream in(out.data);
	in >> a >> b >> c >> d >> e >> f >> g;
	in >> BigEndian<int&>(h) >> LittleEndian<unsigned int&>(i) >> LittleEndian<int&>(j) >> BigEndian<unsigned int&>(k);
	REQUIRE_EQUAL(a,13);
	REQUIRE_EQUAL(b,975);
	REQUIRE_EQUAL(c,-134);
	REQUIRE_EQUAL(d,-2147483648);
	REQUIRE_EQUAL(e,4294967295u);
	REQUIRE_EQUAL(f,0);
	REQUIRE_EQUAL(g,-1);
	REQUIRE_EQUAL(h,-1);
	REQUIRE_EQUAL(i,124);
	REQUIRE_EQUAL(j,9785);
	REQUIRE_EQUAL(k,2101);
}

TEST_CASE( long_long ) {
	StringBinaryOStream out;
	out << 13ll << 13llu << -13ll << 18446744073709551615llu;
       	out << BigEndian<long long>(-1) << LittleEndian<unsigned long long>(18446744073709551615llu) << BigEndian<unsigned long long>(1) << LittleEndian<long long>(31);

	long long a,c,e,h;
	unsigned long long b,d,f,g;

	StringBinaryIStream in(out.data);
	in >> a >> b >> c >> d;
	in >> BigEndian<long long&>(e) >> LittleEndian<unsigned long long&>(f) >> BigEndian<unsigned long long&>(g) >> LittleEndian<long long&>(h);

	REQUIRE_EQUAL(a,13);
	REQUIRE_EQUAL(b,13);
	REQUIRE_EQUAL(c,-13);
	REQUIRE_EQUAL(d,18446744073709551615llu);
	REQUIRE_EQUAL(e,-1);
	REQUIRE_EQUAL(f,18446744073709551615llu);
	REQUIRE_EQUAL(g,1);
	REQUIRE_EQUAL(h,31);
}

TEST_CASE( short ) {
	StringBinaryOStream out;
	out << ((short)13) << ((short)13u) << ((short)-13) << ((short)65535u);
       	out << BigEndian<short>(-1) << LittleEndian<unsigned short>(65535u) << BigEndian<unsigned short>(1) << LittleEndian<short>(-32768);

	short a,c,e,h;
	unsigned short b,d,f,g;

	StringBinaryIStream in(out.data);
	in >> a >> b >> c >> d;
	in >> BigEndian<short&>(e) >> LittleEndian<unsigned short&>(f) >> BigEndian<unsigned short&>(g) >> LittleEndian<short&>(h);

	REQUIRE_EQUAL(a,13);
	REQUIRE_EQUAL(b,13);
	REQUIRE_EQUAL(c,-13);
	REQUIRE_EQUAL(d,65535u);
	REQUIRE_EQUAL(e,-1);
	REQUIRE_EQUAL(f,65535u);
	REQUIRE_EQUAL(g,1);
	REQUIRE_EQUAL(h,-32768);
}

TEST_CASE( char ) {
	StringBinaryOStream out;
	out << 'a' << 'b' << '\0' << '\127' << ((unsigned char)255) << ((char)-128);

	char a,b,c,d,f;
	unsigned char e;

	StringBinaryIStream in(out.data);
	in >> a >> b >> c >> d >> e >> f;

	REQUIRE_EQUAL(a,'a');
	REQUIRE_EQUAL(b,'b');
	REQUIRE_EQUAL(c,'\0');
	REQUIRE_EQUAL(d,'\127');
	REQUIRE_EQUAL(e,255);
	REQUIRE_EQUAL(f,-128);
}

TEST_CASE( float ) {
	StringBinaryOStream out;
	out << 3.0f << 1.0f << LittleEndian<float>(19841.0f) << BigEndian<float>(93121.0f) << 3.1415926536f;

	float a, b, c, d, e;

	StringBinaryIStream in(out.data);
	in >> a >> b >> LittleEndian<float&>(c) >> BigEndian<float&>(d) >> e;

	REQUIRE_EQUAL(a,3.0f);
	REQUIRE_EQUAL(b,1.0f);
	REQUIRE_EQUAL(c,19841.0f);
	REQUIRE_EQUAL(d,93121.0f);
	REQUIRE_EQUAL(e,3.1415926536f);
}

TEST_CASE( double ) {
	StringBinaryOStream out;
	out << 3.0 << 1.0 << LittleEndian<double>(19841.0) << BigEndian<double>(93121.0) << 3.1415926536;

	double a, b, c, d, e;

	StringBinaryIStream in(out.data);
	in >> a >> b >> LittleEndian<double&>(c) >> BigEndian<double&>(d) >> e;

	REQUIRE_EQUAL(a,3.0);
	REQUIRE_EQUAL(b,1.0);
	REQUIRE_EQUAL(c,19841.0);
	REQUIRE_EQUAL(d,93121.0);
	REQUIRE_EQUAL(e,3.1415926536);
};

END_TEST_SUITE();
