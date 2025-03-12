#include <iostream>
#include <cstdlib>
#include <cppunit/TestCase.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/HelperMacros.h>
#include "cpptanu_cfg/cfg_read.h"
#include <filesystem>

using namespace std;
using namespace tanu::cfg;

class JSONCfgTestSuite: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(JSONCfgTestSuite);
    CPPUNIT_TEST(test_load_and_root_singleval_get_noprefix);
    CPPUNIT_TEST(test_load_and_obj_singleval_get_noprefix);
    CPPUNIT_TEST_SUITE_END();
    JSONConfig* json_cfg;

public:
    void setUp() {
        auto test_file_dir = filesystem::current_path() / "testdata";
        setenv("TANULIB_CONF_DIR", test_file_dir.c_str(), 1);
        json_cfg = new JSONConfig{"cpptanu_cfg_utest", "tanu_cfg"};
    }

    void tearDown() {
        delete json_cfg;
    }
protected:
    void test_load_and_root_singleval_get_noprefix();
    void test_load_and_obj_singleval_get_noprefix();
};

void JSONCfgTestSuite::test_load_and_root_singleval_get_noprefix() {
    json_cfg->load("utest.json");
    const int id = json_cfg->get_as_int("id");
    CPPUNIT_ASSERT_EQUAL(32, id);
    const double version = json_cfg->get_as_double("version");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.28, version, 0.01);
    const string name = json_cfg->get_as_str("name");
    CPPUNIT_ASSERT_EQUAL(string {"tako"}, name);
    
}

void JSONCfgTestSuite::test_load_and_obj_singleval_get_noprefix() {
    json_cfg->load("utest.json");
    const int lang_ver = json_cfg->get_as_int("detail/lang-version");
    CPPUNIT_ASSERT_EQUAL(10, lang_ver);
    const double lang_patch = json_cfg->get_as_double("detail/lang-patch");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2864, lang_patch, 0.000001);
    const string lang = json_cfg->get_as_str("detail/lang");
    CPPUNIT_ASSERT_EQUAL(string {"c++"}, lang);
}

CPPUNIT_TEST_SUITE_REGISTRATION(JSONCfgTestSuite);

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
