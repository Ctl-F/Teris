#pragma once


#include "core.h"

#include "spdlog/spdlog.h"

namespace teris {
	class TERIS_API Log
	{
	public:
		static void init();

		inline static std::shared_ptr<spdlog::logger>& get_core_logger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& get_client_logger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}


// core logging macros
#define TS_CORE_FATAL(...) ::teris::Log::get_core_logger()->fatal(__VA_ARGS__)
#define TS_CORE_ERROR(...) ::teris::Log::get_core_logger()->error(__VA_ARGS__)
#define TS_CORE_WARN(...)  ::teris::Log::get_core_logger()->warn(__VA_ARGS__)
#define TS_CORE_INFO(...)  ::teris::Log::get_core_logger()->info(__VA_ARGS__)
#define TS_CORE_TRACE(...) ::teris::Log::get_core_logger()->trace(__VA_ARGS__)

// client log macros
#define TS_FATAL(...) ::teris::Log::get_client_logger()->fatal(__VA_ARGS__)
#define TS_ERROR(...) ::teris::Log::get_client_logger()->error(__VA_ARGS__)
#define TS_WARN(...)  ::teris::Log::get_client_logger()->warn(__VA_ARGS__)
#define TS_INFO(...)  ::teris::Log::get_client_logger()->info(__VA_ARGS__)
#define TS_TRACE(...) ::teris::Log::get_client_logger()->trace(__VA_ARGS__)
