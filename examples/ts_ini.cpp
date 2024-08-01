#include <easy_config_define.h>

int main()
{
    std::string test = "test";
    std::string aaa  = "aaa";
    GET_CONFIG(CONFIG_TYPE_INI)->SetValue("INI.user", test);
    GET_CONFIG(CONFIG_TYPE_INI)->SetValue("INI.aaa", aaa);
    GET_CONFIG(CONFIG_TYPE_INI)->SetValue("JSON.user", test);
    return 0;
}