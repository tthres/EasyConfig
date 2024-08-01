#pragma once

#ifdef _WIN32
#ifdef EASY_CONFIG_EXPORTS
#define EASY_CONFIG_API __declspec(dllexport)
#else
#define EASY_CONFIG_API __declspec(dllimport)
#endif
#endif