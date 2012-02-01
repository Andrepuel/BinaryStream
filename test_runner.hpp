#ifndef __TEST_RUNNER_HPP_48578940151_
#define __TEST_RUNNER_HPP_48578940151_

#include <string>
#include <map>
#include <iostream>

#define NAMESPACE testrunner
#define BEGIN_NAMESPACE namespace NAMESPACE {
#define END_NAMESPACE }

BEGIN_NAMESPACE
typedef const char* CString;

class TestError : public std::exception {
public:
	TestError(const char* failedAssertion);
	~TestError() throw();
	const char* what() const throw();
private:
	const char* msg;
};

class TestCase {
public:
	virtual ~TestCase();
	virtual void run()=0;
};

class TestSuite {
public:
	static TestSuite* getInstance();
//	void add(TestSuite*, CString name);
	void add(TestCase*, CString name);

	void run();
private:
	static TestSuite* instance;
	class dealocator;
	friend class dealocator;
	static dealocator d;

	std::multimap<std::string,TestCase*> cases;
};

END_NAMESPACE

#if 0
struct PrinterEndl {
};
class Printer {
public:
	template <typename T>
	Printer& operator<<(T t) {
		std::cout << t;
		return *this;
	}
};
template <> Printer& Printer::operator<<(int t) { 
	printf("%d",t);
	return *this;
}
template <> Printer& Printer::operator<<(unsigned t) {
	printf("%u",t);
	return *this;
}
template <> Printer& Printer::operator<<(PrinterEndl ) {
	std::cout << std::endl;
	return *this;
}
template <> Printer& Printer::operator<<(long long t) {
	printf("%lld",t);
	return *this;
}
template <> Printer& Printer::operator<<(long long unsigned t) {
	printf("%llu",t);
	return *this;
}
template <> Printer& Printer::operator<<(double t) {
	printf("%lf",t);
	return *this;
}
static Printer cout;
static PrinterEndl endl;
#endif
using std::cout;
using std::endl;

#define BEGIN_TEST_SUITE(suite_name) namespace suite_name {
#define END_TEST_SUITE() }
#define TEST_CASE(test_case) struct test_case##_class : public NAMESPACE::TestCase { \
test_case##_class(NAMESPACE::TestSuite* suite) { suite->add(this,#test_case); } \
void run(); \
}; \
test_case##_class test_case##_instance(NAMESPACE::TestSuite::getInstance()); \
void test_case##_class::run() 

#define REQUIRE(x) if( !(x) ) { cout << __FILE__ << ":" << __LINE__ << " " << #x << endl; throw NAMESPACE::TestError(#x); }
#define REQUIRE_EQUAL(x,y) if( !((x) == (y)) ) { cout << __FILE__ << ":" << __LINE__ << " " << #x << " != " << #y << "(" << (x) << " != " << (y) << ")" << endl; /*throw NAMESPACE::TestError("require equal");*/ }

#endif
