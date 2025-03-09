#include "cpptanu_cfg/cfg_read.h"

#include <fstream>
#include <filesystem>
#include <memory>

namespace tanu::cfg {

    void JSONConfig::load(const std::string& file_name) {
        const std::filesystem::path fpath = (std::filesystem::path(this->conf_dir) / file_name);
        if(!std::filesystem::exists(fpath)) {
            throw TanuCfgException(fpath.string() + " does not exist");
        }
        try {
            std::ifstream ifs(fpath);
            json loaded = json::parse(ifs);
            this->m_cfg_flattened_view = std::make_unique<json>(loaded.flatten());
            this->m_loaded_cfg = std::make_unique<json>(loaded);
        } catch(...) {
            throw TanuCfgException("Json file loading/parsing failed");
        }
    }

    std::optional<std::string> JSONConfig::dump_cfg() {
        if(this->m_loaded_cfg != nullptr) {
            return this->m_loaded_cfg.get()->dump();
        } else {
            return std::nullopt;
        }
    }

    std::optional<std::string> JSONConfig::dump_flattened_view() {
        if(this->m_cfg_flattened_view != nullptr) {
            return this->m_cfg_flattened_view.get()->dump();
        } else {
            return std::nullopt;
        }
    }

    int JSONConfig::get_as_int(const std::string& key) {
        try {
            json flattened = this->m_loaded_cfg.get()->flatten();
            auto v = this->m_loaded_cfg.get()->at(key);
            return v;
        } catch(...) {
            throw new TanuCfgException("getting int value by " + key + " failed");
        }
    }

}