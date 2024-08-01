#pragma once
#include "easy_config.h"

#define CONFIG_TYPE_INI  "ini"
#define CONFIG_TYPE_JSON "json"
#define GET_CONFIG(type) EasyConfig::GetInstance(type)
