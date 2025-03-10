#include "cpptanu_cfg/cfg_read.h"
#include <iostream>
#include <optional>

using namespace std;
using namespace tanu::cfg;

int main() {

    try {
        JSONConfig cfg {"cpptanu", "sample"};
        cfg.load("sample.json");
        cout << cfg.dump_cfg().value_or("NA") << endl;
        cout << cfg.dump_flattened_view().value_or("NA") << endl;
        cout << cfg.get_as_int("id") << endl;
        cout << cfg.get_as_str("/detail/lang") << endl;
        cout << cfg.get_as_double("/version") << endl;
        for(const string& s:cfg.get_as_str_vec("/detail/alias")) {
            cout << s << ',';
        }
        cout << endl;
    } catch(const TanuCfgException& ex) {
        cerr << ex.what() << endl;
    } catch(const json::exception& json_ex) {
        cerr << json_ex.what() << endl;
    } catch(...) {
        cerr << "err" << endl;
    }
    
}