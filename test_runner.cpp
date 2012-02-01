#include "test_runner.hpp"
#include <iostream>

BEGIN_NAMESPACE

TestError::TestError(const char* failedAssertion) : msg(failedAssertion)
{
}
TestError::~TestError() throw() {
}
const char* TestError::what() const throw() {
	return msg;
}

TestCase::~TestCase() {
};

TestSuite* TestSuite::instance=NULL;
TestSuite* TestSuite::getInstance() {
	if( instance == NULL )
		instance = new TestSuite();
	return instance;
}
class TestSuite::dealocator {
public:
	~dealocator() {
		delete TestSuite::instance;
		TestSuite::instance = NULL;
	}
} TestSuite::d;

void TestSuite::add(TestCase* t_case, CString name) {
	cases.insert(std::make_pair(std::string(name),t_case));
}

void TestSuite::run() {
	for( auto each = cases.begin(); each != cases.end(); ++each ) {
		std::cout << "Test case " << each->first.c_str() << "... ";
		try {
			each->second->run();
			std::cout << "OK" << std::endl;
		} catch(const TestError& error) {
			std::cout << "Assertion failed: (" << error.what() << ")" << std::endl;
		} catch(const std::exception& error) {
			std::cout << "Exception throw!" << std::endl;
		}
	}
}

END_NAMESPACE

int main(int argc, char** argv) {
	NAMESPACE::TestSuite::getInstance()->run();
}

TEST_CASE( root_test ) {
	REQUIRE(true);
}
