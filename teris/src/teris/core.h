#pragma once


#ifdef TS_PLATFORM_WINDOWS 

#ifdef TS_BUILD_DLL
#define TERIS_API __declspec(dllexport)
#else 
#define TERIS_API __declspec(dllimport)
#endif
#else
#error Windows is the only supported platform
#endif

#include <string>
#include <vector>
#include <memory>