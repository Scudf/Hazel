#include "hzpch.h"
#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Hazel
{
	logger_ptr Log::s_CoreLogger;
	logger_ptr Log::s_ClientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("HAZEL");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}

	logger_ptr& Log::GetCoreLogger()
	{
		return s_CoreLogger;
	}

	logger_ptr& Log::GetClientLogger()
	{
		return s_ClientLogger;
	}
}
