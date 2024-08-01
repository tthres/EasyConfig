#pragma once
#include "easy_config_export.h"
#include <string>
#include <memory>

class EASY_CONFIG_API EasyConfig
{
public:
    virtual ~EasyConfig() = default;

    static std::shared_ptr<EasyConfig> GetInstance(const std::string& type);

    template<typename T>
    T GetValue(const std::string& key, const T& defaultValue);
    template<>
    std::string EasyConfig::GetValue<std::string>(const std::string& key, const std::string& defaultValue);
    template<>
    int EasyConfig::GetValue<int>(const std::string& key, const int& defaultValue);
    template<>
    float EasyConfig::GetValue<float>(const std::string& key, const float& defaultValue);
    template<>
    bool EasyConfig::GetValue<bool>(const std::string& key, const bool& defaultValue);

    template<typename T>
    void SetValue(const std::string& key, const T& value);
    template<>
    void EasyConfig::SetValue<std::string>(const std::string& key, const std::string& value);
    template<>
    void EasyConfig::SetValue<int>(const std::string& key, const int& value);
    template<>
    void EasyConfig::SetValue<float>(const std::string& key, const float& value);
    template<>
    void EasyConfig::SetValue<bool>(const std::string& key, const bool& value);

protected:
    EasyConfig()                             = default;
    EasyConfig(const EasyConfig&)            = delete;
    EasyConfig& operator=(const EasyConfig&) = delete;

protected:
    virtual std::string GetValueAsString(const std::string& key, const std::string& defaultValue) = 0;
    virtual void        SetValueAsString(const std::string& key, const std::string& value)        = 0;
};
