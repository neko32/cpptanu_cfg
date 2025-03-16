#include <iostream>
#include <cstdlib>
#include <vector>
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
    CPPUNIT_TEST(test_load_fail_due_to_broken_json);
    CPPUNIT_TEST(test_load_and_root_singleval_get_noprefix);
    CPPUNIT_TEST(test_load_and_obj_singleval_get_noprefix);
    CPPUNIT_TEST(test_load_and_root_singleval_get_with_prefix);
    CPPUNIT_TEST(test_load_and_obj_singleval_get_with_prefix);
    CPPUNIT_TEST(test_vec_int_success);
    CPPUNIT_TEST(test_vec_double_success);
    CPPUNIT_TEST(test_vec_str_success);
    CPPUNIT_TEST(test_load_str_fail_due_to_loading_nonstr);
    CPPUNIT_TEST(test_load_str_fail_due_to_key_notfound);
    CPPUNIT_TEST(test_load_int_fail_due_to_loading_nonint);
    CPPUNIT_TEST(test_load_int_fail_due_to_key_notfound);
    CPPUNIT_TEST(test_load_double_fail_due_to_loading_nondouble);
    CPPUNIT_TEST(test_load_double_fail_due_to_key_notfound);
    CPPUNIT_TEST(test_load_vec_str_fail_due_to_loading_nonstr);
    CPPUNIT_TEST(test_load_vec_str_fail_due_to_key_notfound);
    CPPUNIT_TEST(test_load_vec_int_fail_due_to_loading_nonint);
    CPPUNIT_TEST(test_load_vec_int_fail_due_to_key_notfound);
    CPPUNIT_TEST(test_load_vec_double_fail_due_to_loading_nondouble);
    CPPUNIT_TEST(test_load_vec_double_fail_due_to_key_notfound);
    CPPUNIT_TEST(test_load_str_fail_due_to_loading_nonstr);
    CPPUNIT_TEST(test_load_str_fail_due_to_key_notfound);
    CPPUNIT_TEST(test_load_fail_due_to_empty_key);
    CPPUNIT_TEST(test_access_val_before_load);
    CPPUNIT_TEST(test_dump_success);
    CPPUNIT_TEST(test_dump_fail_due_to_before_loading);
    CPPUNIT_TEST(test_load_fail_due_to_no_such_file);
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
    void test_load_fail_due_to_broken_json();
    void test_load_and_root_singleval_get_noprefix();
    void test_load_and_obj_singleval_get_noprefix();
    void test_load_and_root_singleval_get_with_prefix();
    void test_load_and_obj_singleval_get_with_prefix();
    void test_vec_int_success();
    void test_vec_double_success();
    void test_vec_str_success();
    void test_load_str_fail_due_to_loading_nonstr();
    void test_load_str_fail_due_to_key_notfound();
    void test_load_int_fail_due_to_loading_nonint();
    void test_load_int_fail_due_to_key_notfound();
    void test_load_double_fail_due_to_loading_nondouble();
    void test_load_double_fail_due_to_key_notfound();
    void test_load_vec_str_fail_due_to_loading_nonstr();
    void test_load_vec_str_fail_due_to_key_notfound();
    void test_load_vec_int_fail_due_to_loading_nonint();
    void test_load_vec_int_fail_due_to_key_notfound();
    void test_load_vec_double_fail_due_to_loading_nondouble();
    void test_load_vec_double_fail_due_to_key_notfound();
    void test_load_fail_due_to_empty_key();
    void test_access_val_before_load();
    void test_dump_success();
    void test_dump_fail_due_to_before_loading();
    void test_load_fail_due_to_no_such_file();
};

void JSONCfgTestSuite::test_load_fail_due_to_broken_json() {
    try {
        json_cfg->load("broken.json");
    } catch(const TanuCfgException& e) {
        CPPUNIT_ASSERT_EQUAL(string {"Json file loading/parsing failed"}, string{e.what()});
    }
}

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

void JSONCfgTestSuite::test_load_and_root_singleval_get_with_prefix() {
    json_cfg->load("utest.json");
    const int id = json_cfg->get_as_int("/id");
    CPPUNIT_ASSERT_EQUAL(32, id);
    const double version = json_cfg->get_as_double("/version");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(1.28, version, 0.01);
    const string name = json_cfg->get_as_str("/name");
    CPPUNIT_ASSERT_EQUAL(string {"tako"}, name);
}

void JSONCfgTestSuite::test_load_and_obj_singleval_get_with_prefix() {
    json_cfg->load("utest.json");
    const int lang_ver = json_cfg->get_as_int("/detail/lang-version");
    CPPUNIT_ASSERT_EQUAL(10, lang_ver);
    const double lang_patch = json_cfg->get_as_double("/detail/lang-patch");
    CPPUNIT_ASSERT_DOUBLES_EQUAL(0.2864, lang_patch, 0.000001);
    const string lang = json_cfg->get_as_str("/detail/lang");
    CPPUNIT_ASSERT_EQUAL(string {"c++"}, lang);
}

//TODO

void JSONCfgTestSuite::test_load_vec_str_fail_due_to_loading_nonstr() {
    json_cfg->load("utest.json");    
    try {
        json_cfg->get_as_str_vec("/detail/appendix/platform_ids");
        CPPUNIT_FAIL("shouldn't reach here");
    } catch(const TanuCfgException& ex) {
        CPPUNIT_ASSERT_EQUAL(string{"/detail/appendix/platform_ids\'s value is not string"}, string{ex.what()});
    }
}

void JSONCfgTestSuite::test_load_vec_int_fail_due_to_loading_nonint() {
    json_cfg->load("utest.json");    
    try {
        json_cfg->get_as_int_vec("/tags");
        CPPUNIT_FAIL("shouldn't reach here");
    } catch(const TanuCfgException& ex) {
        CPPUNIT_ASSERT_EQUAL(string{"/tags\'s value is not integer"}, string{ex.what()});
    }
}

void JSONCfgTestSuite::test_load_vec_double_fail_due_to_loading_nondouble() {
    json_cfg->load("utest.json");    
    try {
        json_cfg->get_as_double_vec("/tags");
        CPPUNIT_FAIL("shouldn't reach here");
    } catch(const TanuCfgException& ex) {
        CPPUNIT_ASSERT_EQUAL(string{"/tags\'s value is not double"}, string{ex.what()});
    }
}

void JSONCfgTestSuite::test_load_vec_int_fail_due_to_key_notfound() {
    json_cfg->load("utest.json");
    try {
        json_cfg->get_as_int_vec("/nowawawa2");
        CPPUNIT_FAIL("shouldn't reach here");
    } catch(const TanuCfgException& json_e) {
        string msg {json_e.what()};
        CPPUNIT_ASSERT_EQUAL(true, msg.find("key \'/nowawawa2\' not found") != std::string::npos);
    }
}

void JSONCfgTestSuite::test_load_vec_double_fail_due_to_key_notfound() {
    json_cfg->load("utest.json");
    try {
        json_cfg->get_as_double_vec("/nowawawa3");
        CPPUNIT_FAIL("shouldn't reach here");
    } catch(const TanuCfgException& json_e) {
        string msg {json_e.what()};
        CPPUNIT_ASSERT_EQUAL(true, msg.find("key \'/nowawawa3\' not found") != std::string::npos);
    }
}

void JSONCfgTestSuite::test_load_vec_str_fail_due_to_key_notfound() {
    json_cfg->load("utest.json");
    try {
        json_cfg->get_as_str_vec("/nowawawa");
        CPPUNIT_FAIL("shouldn't reach here");
    } catch(const TanuCfgException& json_e) {
        string msg {json_e.what()};
        CPPUNIT_ASSERT_EQUAL(true, msg.find("key \'/nowawawa\' not found") != std::string::npos);
    }
}

//TODO END

void JSONCfgTestSuite::test_load_str_fail_due_to_loading_nonstr() {
    json_cfg->load("utest.json");    
    try {
        json_cfg->get_as_str("/id");
        CPPUNIT_FAIL("shouldn't reach here");
    } catch(const TanuCfgException& ex) {
        CPPUNIT_ASSERT_EQUAL(string{"/id's value is not string"}, string{ex.what()});
    }
}

void JSONCfgTestSuite::test_load_int_fail_due_to_loading_nonint() {
    json_cfg->load("utest.json");    
    try {
        json_cfg->get_as_int("/name");
        CPPUNIT_FAIL("shouldn't reach here");
    } catch(const TanuCfgException& ex) {
        CPPUNIT_ASSERT_EQUAL(string{"/name's value is not integer"}, string{ex.what()});
    }
}

void JSONCfgTestSuite::test_load_double_fail_due_to_loading_nondouble() {
    json_cfg->load("utest.json");    
    try {
        json_cfg->get_as_double("/name");
        CPPUNIT_FAIL("shouldn't reach here");
    } catch(const TanuCfgException& ex) {
        CPPUNIT_ASSERT_EQUAL(string{"/name's value is not double"}, string{ex.what()});
    }
}

void JSONCfgTestSuite::test_load_int_fail_due_to_key_notfound() {
    json_cfg->load("utest.json");
    try {
        json_cfg->get_as_int("/nowawawa2");
        CPPUNIT_FAIL("shouldn't reach here");
    } catch(const TanuCfgException& json_e) {
        string msg {json_e.what()};
        CPPUNIT_ASSERT_EQUAL(true, msg.find("json::exception") != std::string::npos);
        CPPUNIT_ASSERT_EQUAL(true, msg.find("key \'/nowawawa2\' not found") != std::string::npos);
    }
}

void JSONCfgTestSuite::test_load_double_fail_due_to_key_notfound() {
    json_cfg->load("utest.json");
    try {
        json_cfg->get_as_double("/nowawawa3");
        CPPUNIT_FAIL("shouldn't reach here");
    } catch(const TanuCfgException& json_e) {
        string msg {json_e.what()};
        CPPUNIT_ASSERT_EQUAL(true, msg.find("json::exception") != std::string::npos);
        CPPUNIT_ASSERT_EQUAL(true, msg.find("key \'/nowawawa3\' not found") != std::string::npos);
    }
}

void JSONCfgTestSuite::test_load_str_fail_due_to_key_notfound() {
    json_cfg->load("utest.json");
    try {
        json_cfg->get_as_str("/nowawawa");
        CPPUNIT_FAIL("shouldn't reach here");
    } catch(const TanuCfgException& json_e) {
        string msg {json_e.what()};
        CPPUNIT_ASSERT_EQUAL(true, msg.find("json::exception") != std::string::npos);
        CPPUNIT_ASSERT_EQUAL(true, msg.find("key \'/nowawawa\' not found") != std::string::npos);
    }
}

void JSONCfgTestSuite::test_vec_int_success() {
    json_cfg->load("utest.json");    
    vector<int> expected {1, 0};
    vector<int> pids = json_cfg->get_as_int_vec("detail/appendix/platform_ids");
    CPPUNIT_ASSERT(expected == pids);
}

void JSONCfgTestSuite::test_vec_double_success() {
    json_cfg->load("utest.json");    
    vector<double> expected {210.45, 18.10, 395.45};
    vector<double> fids = json_cfg->get_as_double_vec("detail/appendix/feat_ids");
    CPPUNIT_ASSERT(expected == fids);
}

void JSONCfgTestSuite::test_vec_str_success() {
    json_cfg->load("utest.json");    
    cout << json_cfg->dump_flattened_view().value_or("NA") << endl;
    vector<string> expected {"neko", "cat", "pokora"};
    vector<string> tags = json_cfg->get_as_str_vec("tags");
    CPPUNIT_ASSERT(expected == tags);
    vector<string> expected_aliases {"cpp", "c++", "C++"};
    vector<string> aliases = json_cfg->get_as_str_vec("/detail/alias");
    CPPUNIT_ASSERT(expected_aliases == aliases);
}

void JSONCfgTestSuite::test_load_fail_due_to_empty_key() {
    json_cfg->load("utest.json");

    try {
        json_cfg->get_as_int("");
        CPPUNIT_FAIL("shouldn't reach here");
    } catch(const TanuCfgException& json_e) {
        string msg {json_e.what()};
        CPPUNIT_ASSERT_EQUAL(true, msg.find("json::exception") != std::string::npos);
        CPPUNIT_ASSERT_EQUAL(true, msg.find("key \'/\' not found") != std::string::npos);
    }

    try {
        json_cfg->get_as_str("");
        CPPUNIT_FAIL("shouldn't reach here");
    } catch(const TanuCfgException& json_e) {
        string msg {json_e.what()};
        CPPUNIT_ASSERT_EQUAL(true, msg.find("json::exception") != std::string::npos);
        CPPUNIT_ASSERT_EQUAL(true, msg.find("key \'/\' not found") != std::string::npos);
    }

    try {
        json_cfg->get_as_double("");
        CPPUNIT_FAIL("shouldn't reach here");
    } catch(const TanuCfgException& json_e) {
        string msg {json_e.what()};
        CPPUNIT_ASSERT_EQUAL(true, msg.find("json::exception") != std::string::npos);
        CPPUNIT_ASSERT_EQUAL(true, msg.find("key \'/\' not found") != std::string::npos);
    }

    try {
        json_cfg->get_as_int("/");
        CPPUNIT_FAIL("shouldn't reach here");
    } catch(const TanuCfgException& json_e) {
        string msg {json_e.what()};
        CPPUNIT_ASSERT_EQUAL(true, msg.find("json::exception") != std::string::npos);
        CPPUNIT_ASSERT_EQUAL(true, msg.find("key \'/\' not found") != std::string::npos);
    }

    try {
        json_cfg->get_as_str("/");
        CPPUNIT_FAIL("shouldn't reach here");
    } catch(const TanuCfgException& json_e) {
        string msg {json_e.what()};
        CPPUNIT_ASSERT_EQUAL(true, msg.find("json::exception") != std::string::npos);
        CPPUNIT_ASSERT_EQUAL(true, msg.find("key \'/\' not found") != std::string::npos);
    }

    try {
        json_cfg->get_as_double("/");
        CPPUNIT_FAIL("shouldn't reach here");
    } catch(const TanuCfgException& json_e) {
        string msg {json_e.what()};
        CPPUNIT_ASSERT_EQUAL(true, msg.find("json::exception") != std::string::npos);
        CPPUNIT_ASSERT_EQUAL(true, msg.find("key \'/\' not found") != std::string::npos);
    }
}

void JSONCfgTestSuite::test_access_val_before_load() {
    try {
        json_cfg->get_as_int("id");
        CPPUNIT_FAIL("shouldn't reach here");
    } catch(const TanuCfgException& e) {
        CPPUNIT_ASSERT_EQUAL(string {"Json config hasn't loaded yet"}, string{e.what()});
    }

    try {
        json_cfg->get_as_double("version");
        CPPUNIT_FAIL("shouldn't reach here");
    } catch(const TanuCfgException& e) {
        CPPUNIT_ASSERT_EQUAL(string {"Json config hasn't loaded yet"}, string{e.what()});
    }

    try {
        json_cfg->get_as_str("name");
        CPPUNIT_FAIL("shouldn't reach here");
    } catch(const TanuCfgException& e) {
        CPPUNIT_ASSERT_EQUAL(string {"Json config hasn't loaded yet"}, string{e.what()});
    }

    try {
        json_cfg->get_as_str_vec("tags");
        CPPUNIT_FAIL("shouldn't reach here");
    } catch(const TanuCfgException& e) {
        CPPUNIT_ASSERT_EQUAL(string {"Json config hasn't loaded yet"}, string{e.what()});
    }

    try {
        json_cfg->get_as_int_vec("detail/appendix/platform_ids");
        CPPUNIT_FAIL("shouldn't reach here");
    } catch(const TanuCfgException& e) {
        CPPUNIT_ASSERT_EQUAL(string {"Json config hasn't loaded yet"}, string{e.what()});
    }

    try {
        json_cfg->get_as_double_vec("detail/appendix/feat_ids");
        CPPUNIT_FAIL("shouldn't reach here");
    } catch(const TanuCfgException& e) {
        CPPUNIT_ASSERT_EQUAL(string {"Json config hasn't loaded yet"}, string{e.what()});
    }

}

void JSONCfgTestSuite::test_dump_success() {
    json_cfg->load("utest.json");
    CPPUNIT_ASSERT_EQUAL(true, json_cfg->dump_cfg().has_value());
    CPPUNIT_ASSERT_EQUAL(true, json_cfg->dump_flattened_view().has_value());
}

void JSONCfgTestSuite::test_dump_fail_due_to_before_loading() {
    CPPUNIT_ASSERT_EQUAL(false, json_cfg->dump_cfg().has_value());
    CPPUNIT_ASSERT_EQUAL(false, json_cfg->dump_flattened_view().has_value());
}

void JSONCfgTestSuite::test_load_fail_due_to_no_such_file() {
    try {
        json_cfg->load("neko.json");
        CPPUNIT_FAIL("shouldn't reach here");
    } catch(const TanuCfgException& e) {
        const string keyword = "neko.json does not exist";
        const string e_msg{e.what()};
        CPPUNIT_ASSERT_EQUAL(true, e_msg.find(keyword) != e_msg.npos);
    }
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
