#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Reyes {
	class REYES_API Log {
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger> &GetClientLogger() { return s_ClientLogger; }
	};
}