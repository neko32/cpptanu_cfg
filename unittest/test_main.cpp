#include <iostream>
#include <cppunit/TestCase.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/HelperMacros.h>
#include "../include/myneko/myneko.h"

using namespace std;
using namespace tanu::sample;

class MyTestSuite: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(MyTestSuite);
    CPPUNIT_TEST(test_name);
    CPPUNIT_TEST(test_age);
    CPPUNIT_TEST(test_name_b64);
    CPPUNIT_TEST_SUITE_END();
    MyNeko *neko;
public:
    void setUp() {
        neko = new MyNeko {5, "nekorin"};
    }
    void tearDown() {
        delete neko;
    }
protected:
    void test_name();
    void test_age();
    void test_name_b64();

};

void MyTestSuite::test_name() {
    string expected = "nekorin";
    string actual = neko->name();
    CPPUNIT_ASSERT_EQUAL(expected, actual);
}

void MyTestSuite::test_age() {
    CPPUNIT_ASSERT(5 == neko->age());
}

void MyTestSuite::test_name_b64() {
    string expected = "bmVrb3Jpbg==";
    string actual = neko->name_as_b64();
    CPPUNIT_ASSERT_EQUAL(expected, actual);
}

CPPUNIT_TEST_SUITE_REGISTRATION(MyTestSuite);

int main() {
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestResultCollector collected_results;
    runner.eventManager().addListener(&collected_results);
    CppUnit::BriefTestProgressListener progress;
    runner.eventManager().addListener(&progress);
    runner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
    runner.run();

    CppUnit::CompilerOutputter outputter(&collected_results, cerr);
    outputter.write();

    return collected_results.wasSuccessful() ? 0 : 1;
}
