#pragma once

#include "easy_config.h"
#include <map>
#include <filesystem>

class EasyConfigIni : public EasyConfig
{
public:
    static std::shared_ptr<EasyConfigIni> GetInstance();

    std::string GetValueAsString(const std::string& key, const std::string& defaultValue) override;
    void        SetValueAsString(const std::string& key, const std::string& value) override;
private:
    EasyConfigIni();
    std::map<std::string, std::string> _data;
    std::filesystem::path              _iniPath;
};