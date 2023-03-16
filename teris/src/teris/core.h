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

#ifdef TS_ENABLE_ASSERTS
#define TS_ASSERT(x, ...) { if(!(x)) { TS_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define TS_CORE_ASSERT(x, ...) { if(!(x)) { TS_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define TS_VERIFY(x, ...) { if(!(x)) { TS_ERROR("Verification Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define TS_ASSERT(x, ...)
#define TS_CORE_ASSERT(x, ...)
#define TS_VERIFY(x, ...) (x)
#endif

#define BIT(x) (1 << x)

#include "../tpch.h"

#include "Log.h"


#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)