/*
Copyright (C) 2012 André Puel

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

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
