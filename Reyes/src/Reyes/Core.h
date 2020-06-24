#pragma once

#ifdef REY_WINDOWS
#ifdef REY_DYNAMIC
#ifdef REY_EXPORT_LIBRARY
#define REYES_API __declspec(dllexport)
#else
#define REYES_API __declspec(dllimport)
#endif // REY_EXPORT_LIBRARY
#else
#define REYES_API
#endif //REY_DYNAMIC
#else
#error The Reyes Engine currently only supports Windows
#endif // REY_WINDOWS

#ifdef REY_DEBUG
#define REY_LOG_ENABLED
#define REY_ASSERT_ENABLED
#endif

#ifdef REY_LOG_ENABLED
#define REY_CORE_FATAL(...)  ::Reyes::Log::GetCoreLogger()->critical(__VA_ARGS__);
#define REY_CORE_ERROR(...)  ::Reyes::Log::GetCoreLogger()->error(__VA_ARGS__);
#define REY_CORE_WARN(...)   ::Reyes::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define REY_CORE_INFO(...)   ::Reyes::Log::GetCoreLogger()->info(__VA_ARGS__);
#define REY_CORE_TRACE(...)  ::Reyes::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define REY_LOG_FATAL(...)   ::Reyes::Log::GetClientLogger()->critical(__VA_ARGS__);
#define REY_LOG_ERROR(...)   ::Reyes::Log::GetClientLogger()->error(__VA_ARGS__);
#define REY_LOG_WARN(...)    ::Reyes::Log::GetClientLogger()->warn(__VA_ARGS__);
#define REY_LOG_INFO(...)    ::Reyes::Log::GetClientLogger()->info(__VA_ARGS__);
#define REY_LOG_TRACE(...)   ::Reyes::Log::GetClientLogger()->trace(__VA_ARGS__);
#else
#define REY_CORE_FATAL(...)
#define REY_CORE_ERROR(...)
#define REY_CORE_WARN(...)
#define REY_CORE_INFO(...)
#define REY_CORE_TRACE(...)
#define REY_LOG_FATAL(...)
#define REY_LOG_ERROR(...)
#define REY_LOG_WARN(...)
#define REY_LOG_INFO(...)
#define REY_LOG_TRACE(...)
#endif

#ifdef REY_ASSERT_ENABLED
#define REY_ASSERT(x, ...) {if (!(x)) {REY_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak();}}
#define REY_CORE_ASSERT(x, ...) {if (!(x)) {REY_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
#define REY_ASSERT(x, ...)
#define REY_CORE_ASSERT(x, ...)
#endif // REY_ASSERT_ENABLED

#define BIT(x) (1u << x)

#define REY_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)