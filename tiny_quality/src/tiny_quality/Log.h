#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace tiny_quality {

	class TINY_QUALITY_API Log {
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr < spdlog::logger> s_ClientLogger;
	};

}

//Core log macros
#define TQ_CORE_TRACE(...)		::tiny_quality::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define TQ_CORE_INFO(...)		::tiny_quality::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TQ_CORE_WARN(...)		::tiny_quality::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TQ_CORE_ERROR(...)		::tiny_quality::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TQ_CORE_FATAL(...)		::tiny_quality::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client log macros
#define TQ_TRACE(...)			::tiny_quality::Log::GetClientLogger()->trace(__VA_ARGS__)
#define TQ_INFO(...)			::tiny_quality::Log::GetClientLogger()->info(__VA_ARGS__)
#define TQ_WARN(...)			::tiny_quality::Log::GetClientLogger()->warn(__VA_ARGS__)
#define TQ_ERROR(...)			::tiny_quality::Log::GetClientLogger()->error(__VA_ARGS__)
#define TQ_FATAL(...)			::tiny_quality::Log::GetClientLogger()->fatal(__VA_ARGS__)