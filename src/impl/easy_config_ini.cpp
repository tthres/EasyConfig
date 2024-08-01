#include "easy_config_ini.h"
#include "easy_config_utils.h"
#include <fstream>
#include <mutex>

namespace
{

// 去除字符串首尾的空白字符
std::string Trim(const std::string& str)
{
    const std::string whitespace = " \t\n\r\f\v";
    size_t            start      = str.find_first_not_of(whitespace);
    if (start == std::string::npos)
        return "";
    size_t end = str.find_last_not_of(whitespace);
    return str.substr(start, end - start + 1);
}

std::map<std::string, std::string> ReadIniFile(std::ifstream& file)
{
    std::string line;
    std::string currentSection;

    std::map<std::string, std::string> data;
    while (std::getline(file, line))
    {
        line = Trim(line);

        if (line.empty() || line[0] == ';' || line[0] == '#')
        {
            continue;
        }

        // 处理section
        if (line[0] == '[' && line[line.length() - 1] == ']')
        {
            currentSection = line.substr(1, line.length() - 2);
            continue;
        }

        // 处理key-value
        size_t pos = line.find('=');
        if (pos != std::string::npos)
        {
            std::string key   = Trim(line.substr(0, pos));
            std::string value = Trim(line.substr(pos + 1));

            std::string fullKey = currentSection.empty() ? key : currentSection + "." + key;
            data[fullKey]       = value;
        }
    }
    return data;
}

void CreateIniFile(const std::filesystem::path& path)
{
    utils::CreateConfigDir();
    std::ofstream file(path, std::ios::out | std::ios::trunc);
    if (file.is_open())
    {
        file.close();
    }
    else
    {
        throw std::runtime_error("Failed to create ini file: " + path.string());
    }
}

// 将 "section.key" 格式的数据解析到嵌套的 map 中
void ParseKeyValue(std::map<std::string, std::map<std::string, std::string>>& sections, const std::map<std::string, std::string>& data)
{
    for (const auto& [fullKey, value] : data)
    {
        size_t dotPos = fullKey.find('.');
        if (dotPos == std::string::npos)
        {
            // 如果没有找到点号，使用默认 section
            sections["DEFAULT"][fullKey] = value;
        }
        else
        {
            std::string section    = fullKey.substr(0, dotPos);
            std::string key        = fullKey.substr(dotPos + 1);
            sections[section][key] = value;
        }
    }
}

void WriteIniFile(const std::filesystem::path& path, const std::map<std::string, std::string>& data)
{
    std::ofstream file(path, std::ios::out | std::ios::trunc);
    if (file.is_open())
    {
        std::map<std::string, std::map<std::string, std::string>> sections;

        ParseKeyValue(sections, data);

        // 写入文件
        for (const auto& [section, entries] : sections)
        {
            file << "[" << section << "]" << std::endl;
            for (const auto& [key, value] : entries)
            {
                file << key << "=" << value << std::endl;
            }
            file << std::endl; // 在每个 section 后添加一个空行，提高可读性
        }

        file.close();
    }
}

} // namespace

std::shared_ptr<EasyConfigIni> EasyConfigIni::GetInstance()
{
    static std::mutex                     instanceMutex;
    static std::shared_ptr<EasyConfigIni> instance;

    std::lock_guard<std::mutex> lock(instanceMutex);
    if (!instance)
    {
        instance.reset(new EasyConfigIni());
    }
    return instance;
}

EasyConfigIni::EasyConfigIni() : _iniPath(utils::GetConfigPath(CONFIG_TYPE_INI))
{
    std::ifstream file(_iniPath, std::ios::in);
    if (file.is_open())
    {
        _data = ReadIniFile(file);
        file.close();
    }
    else // 创建配置文件
    {
        CreateIniFile(_iniPath);
    }
}

std::string EasyConfigIni::GetValueAsString(const std::string& key, const std::string& defaultValue)
{
    auto it = _data.find(key);
    if (it != _data.end())
    {
        return it->second;
    }

    // 修改配置文件
    _data[key] = defaultValue;
    WriteIniFile(_iniPath, _data);

    return defaultValue;
}

void EasyConfigIni::SetValueAsString(const std::string& key, const std::string& value)
{
    _data[key] = value;
    WriteIniFile(_iniPath, _data);
}