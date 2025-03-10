#include "cpptanu_cfg/cfg_read.h"

#include <iostream>
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

    int JSONConfig::get_as_int(const std::string& key_o) {
        std::string key = key_o;
        if(key.front() != '/') key.insert(key.begin(), '/');
        try {
            auto v = this->m_cfg_flattened_view.get()->at(key);
            if(!v.is_number_integer()) {
                throw TanuCfgException(key + "'s value is not integer");
            }
            return v;
        } catch(const json::exception& json_ex) {
            throw;
        } catch(const TanuCfgException& ex) {
            throw ex;
        } 
    }

    std::string JSONConfig::get_as_str(const std::string& key_o) {
        std::string key = key_o;
        if(key.front() != '/') key.insert(key.begin(), '/');
        try {
            auto v = this->m_cfg_flattened_view.get()->at(key);
            if(!v.is_string()) {
                throw TanuCfgException(key + "'s value is not string");
            }
            return v;
        } catch(const json::exception& json_ex) { 
            throw;
        } catch(const TanuCfgException& ex) {
            std::cerr << ex.what() << std::endl;
            throw;
        } 
    }

    double JSONConfig::get_as_double(const std::string& key_o) {
        std::string key = key_o;
        if(key.front() != '/') key.insert(key.begin(), '/');
        try {
            auto v = this->m_cfg_flattened_view.get()->at(key);
            if(!v.is_number_float()) {
                throw TanuCfgException(key + "'s value is not double");
            }
            return v;
        } catch(const json::exception& json_ex) { 
            throw new TanuCfgException("getting int value by " + key + " failed:" + json_ex.what());
        } catch(const TanuCfgException& e) {
            throw e;
        } catch(...) {
            throw new TanuCfgException("getting int value by " + key + " failed");
        }
    }

    std::vector<double> JSONConfig::get_as_double_vec(const std::string& key_o) {
        std::string key = key_o;
        if(key.front() != '/') key.insert(key.begin(), '/');
        try {
            // [TODO]
            std::vector<double> v;
            return v;

        } catch(const json::exception& json_ex) { 
            throw new TanuCfgException("getting int value by " + key + " failed:" + json_ex.what());
        }  catch(const TanuCfgException& ex) {
            throw ex;
        }
        catch(...) {
            throw new TanuCfgException("getting int value by " + key + " failed");
        }
    }

    std::vector<int> JSONConfig::get_as_int_vec(const std::string& key) {
        try {
            // [TODO]
            std::vector<int> v;
            return v;

        } catch(const json::exception& json_ex) { 
            throw new TanuCfgException("getting int value by " + key + " failed:" + json_ex.what());
        }  catch(const TanuCfgException& ex) {
            throw ex;
        }
        catch(...) {
            throw new TanuCfgException("getting int value by " + key + " failed");
        }
    }

    std::vector<std::string> JSONConfig::get_as_str_vec(const std::string& key_o) {
        std::string key_base = key_o;
        std::string key;
        int idx = 0;
        if(key.front() != '/') key.insert(key.begin(), '/');
        try {
            std::vector<std::string> rez_v;
            while(true) {
                key = key_base + "/" + char(idx + '0');
                if(this->m_cfg_flattened_view.get()->contains(key)) {
                    auto v = this->m_cfg_flattened_view.get()->at(key);
                    if(!v.is_string()) {
                        throw TanuCfgException(key + "'s value is not string");
                    }
                    rez_v.push_back(v);
                    idx++;
                } else {
                    break;
                }
            }
            if(rez_v.size() == 0) {
                throw TanuCfgException(key + " not found");
            }
            return rez_v;

        } catch(const json::exception& json_ex) { 
            throw new TanuCfgException("getting int value by " + key + " failed:" + json_ex.what());
        }  catch(const TanuCfgException& ex) {
            throw ex;
        }
        catch(...) {
            throw new TanuCfgException("getting int value by " + key + " failed");
        }
    }
}