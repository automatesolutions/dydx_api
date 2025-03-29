#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <string>
#include <map>
#include <fstream>
#include <algorithm>

class EnvConfig {
private:
    std::map<std::string, std::string> config;

    static void trim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
            return !std::isspace(ch);
        }));
        s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    }

public:
    explicit EnvConfig(const std::string& filename = ".env") {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open " + filename);
        }
        std::string line;
        
        while (std::getline(file, line)) {
            size_t comment_pos = line.find('#');
            if (comment_pos != std::string::npos) {
                line = line.substr(0, comment_pos);
            }
            
            trim(line);
            if (line.empty()) continue;
            
            size_t delimiter_pos = line.find('=');
            if (delimiter_pos != std::string::npos) {
                std::string key = line.substr(0, delimiter_pos);
                std::string value = line.substr(delimiter_pos + 1);
                
                trim(key);
                trim(value);
                
                if (value.size() >= 2 && value.front() == '"' && value.back() == '"') {
                    value = value.substr(1, value.size() - 2);
                }
                
                config[key] = value;
            }
        }
    }

    std::string get(const std::string& key, const std::string& defaultValue = "") const {
        auto it = config.find(key);
        return (it != config.end()) ? it->second : defaultValue;
    }

    int getInt(const std::string& key, int defaultValue = 0) const {
        try {
            return std::stoi(get(key, std::to_string(defaultValue)));
        } catch (...) {
            return defaultValue;
        }
    }
};

#endif