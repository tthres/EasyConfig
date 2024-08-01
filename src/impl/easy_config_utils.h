#pragma once
#include "easy_config_define.h"

#include <string>
#include <sstream>
#include <filesystem>
#ifdef _WIN32
#include <windows.h>
#include <shlobj.h>
#elif defined(__APPLE__) || defined(__linux__)
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#endif

namespace utils
{
template<typename T>
static std::string ToString(const T& value)
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}

static std::string GetExeName()
{
#ifdef _WIN32
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::filesystem::path path(buffer);
    return path.stem().string();
#else
    char    buffer[1024];
    ssize_t len = readlink("/proc/self/exe", buffer, sizeof(buffer) - 1);
    if (len != -1)
    {
        buffer[len] = '\0';
        std::filesystem::path path(buffer);
        return path.stem().string();
    }
    return "";
#endif
}

static std::string GetAppDataPath()
{
#ifdef _WIN32
    PWSTR path = NULL;
    if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, NULL, &path)))
    {
        std::wstring ws(path);
        CoTaskMemFree(path);
        return std::string(ws.begin(), ws.end());
    }
#else
    const char* home = getenv("HOME");
    if (home)
    {
        return std::string(home) + "/.config";
    }
#endif
    return "";
}

static std::filesystem::path GetConfigPath(const std::string& type)
{
    std::filesystem::path path = std::filesystem::path(GetAppDataPath()) / GetExeName() / GetExeName();
    if (type == CONFIG_TYPE_INI)
    {
        return path.replace_extension(".ini");
    }
    else if (type == CONFIG_TYPE_JSON)
    {
        return path.replace_extension(".json");
    }
    return std::filesystem::path();
}

// 创建文件夹
static void CreateConfigDir()
{
    std::filesystem::create_directories(std::filesystem::path(GetAppDataPath()) / GetExeName());
}

} // namespace utils