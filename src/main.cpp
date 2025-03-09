#include "cpptanu_cfg/cfg_read.h"
#include <iostream>
#include <optional>

using namespace std;
using namespace tanu::cfg;

int main() {

    JSONConfig cfg {"cpptanu", "sample"};
    cfg.load("sample.json");
    cout << cfg.dump_cfg().value_or("NA") << endl;
    cout << cfg.dump_flattened_view().value_or("NA") << endl;
    cout << cfg.get_as_int("id") << endl;
    
}