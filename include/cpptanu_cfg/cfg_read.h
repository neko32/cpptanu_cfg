#pragma once
#ifndef __CFG_READ_H__
#define __CFG_READ_H__

#include "nlohmann/json.hpp"
#include <string>
#include <memory>
#include <cstdlib>
#include <filesystem>
#include <exception>
#include <vector>
#include <optional>

using json = nlohmann::json;

namespace tanu::cfg {

    static const std::string CONF_DIR_ENV_VAR_NAME {"TANULIB_CONF_DIR"};

    class JSONConfig {
    private:
        std::string m_group_name;
        std::string m_app_name;
        std::unique_ptr<json> m_loaded_cfg;
        std::unique_ptr<json> m_cfg_flattened_view;
        std::string conf_dir;
    public:
        JSONConfig(
            const std::string& group_name, 
            const std::string& app_name): m_group_name(group_name), m_app_name(app_name), m_loaded_cfg(nullptr), m_cfg_flattened_view(nullptr) {
                std::string conf_base {getenv(CONF_DIR_ENV_VAR_NAME.c_str())};
                conf_dir = (std::filesystem::path(conf_base) / m_group_name / m_app_name).string();
            }
        ~JSONConfig() {
            if(m_loaded_cfg != nullptr) {
                m_loaded_cfg.release();
                m_loaded_cfg = nullptr;
                m_cfg_flattened_view.release();
                m_cfg_flattened_view = nullptr;
            }
        }
        
        std::optional<std::string> dump_cfg();
        std::optional<std::string> dump_flattened_view();
        void load(const std::string& cfg_file_name);
        int get_as_int(const std::string& key);
        std::string get_as_str(const std::string& key);
        double get_as_double(const std::string& key);
        std::vector<int> get_as_int_vec(const std::string& key);
        std::vector<std::string> get_as_str_vec(const std::string& key);
        std::vector<double> get_as_double_vec(const std::string& key);
    };

    class TanuCfgException:public std::exception {
    private:
        std::string m_reason;
    public:
        TanuCfgException(const std::string& reason):m_reason(reason){}
        const char* what() const noexcept override {
            return m_reason.c_str();
        }
    };

}


#endif