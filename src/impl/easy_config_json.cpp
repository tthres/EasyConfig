#include "easy_config_json.h"
#include <mutex>

EasyConfigJson::EasyConfigJson()
{
}

std::shared_ptr<EasyConfigJson> EasyConfigJson::GetInstance()
{
    static std::mutex                      instanceMutex;
    static std::shared_ptr<EasyConfigJson> instance;

    std::lock_guard<std::mutex> lock(instanceMutex);
    if (!instance)
    {
        instance.reset(new EasyConfigJson());
    }
    return instance;
}

std::string EasyConfigJson::GetValueAsString(const std::string& key, const std::string& defaultValue)
{
    return defaultValue;
}

void EasyConfigJson::SetValueAsString(const std::string& key, const std::string& value)
{
}
