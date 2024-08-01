#include "easy_config.h"
#include "easy_config_define.h"
#include "easy_config_ini.h"
#include "easy_config_json.h"
#include <mutex>
#include <sstream>

template<typename T>
T EasyConfig::GetValue(const std::string& key, const T& defaultValue)
{
    throw std::runtime_error("getValue not implemented for this type");
}

template<typename T>
void EasyConfig::SetValue(const std::string& key, const T& value)
{
    throw std::runtime_error("setValue not implemented for this type");
}

template<>
std::string EasyConfig::GetValue<std::string>(const std::string& key, const std::string& defaultValue)
{
    return GetValueAsString(key, defaultValue);
}

template<>
int EasyConfig::GetValue<int>(const std::string& key, const int& defaultValue)
{
    return std::stoi(GetValueAsString(key, std::to_string(defaultValue)));
}

template<>
float EasyConfig::GetValue<float>(const std::string& key, const float& defaultValue)
{
    return std::stof(GetValueAsString(key, std::to_string(defaultValue)));
}

template<>
bool EasyConfig::GetValue<bool>(const std::string& key, const bool& defaultValue)
{
    std::string value = GetValueAsString(key, std::to_string(defaultValue));
    return value == "true" || value == "1" || value == "yes";
}

template<>
void EasyConfig::SetValue<std::string>(const std::string& key, const std::string& value)
{
    SetValueAsString(key, value);
}

template<>
void EasyConfig::SetValue<int>(const std::string& key, const int& value)
{
    SetValueAsString(key, std::to_string(value));
}

template<>
void EasyConfig::SetValue<float>(const std::string& key, const float& value)
{
    SetValueAsString(key, std::to_string(value));
}

template<>
void EasyConfig::SetValue<bool>(const std::string& key, const bool& value)
{
    SetValueAsString(key, value ? "true" : "false");
}

std::shared_ptr<EasyConfig> EasyConfig::GetInstance(const std::string& type)
{
    static std::mutex           instanceMutex;
    std::lock_guard<std::mutex> lock(instanceMutex);
    if (type == CONFIG_TYPE_INI)
    {
        return EasyConfigIni::GetInstance();
    }
    else if (type == CONFIG_TYPE_JSON)
    {
        return EasyConfigJson::GetInstance();
    }
    throw std::runtime_error("Invalid config type");
}
