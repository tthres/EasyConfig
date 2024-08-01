#pragma once

#include "easy_config.h"
#include <map>
#include <filesystem>

class EasyConfigJson : public EasyConfig
{
public:
    static std::shared_ptr<EasyConfigJson> GetInstance();

    std::string GetValueAsString(const std::string& key, const std::string& defaultValue) override;
    void        SetValueAsString(const std::string& key, const std::string& value) override;
private:
    EasyConfigJson();
    std::filesystem::path _jsonPath;
};