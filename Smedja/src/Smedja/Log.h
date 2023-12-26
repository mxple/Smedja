#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Smedja {

class Log {
    static std::shared_ptr<spdlog::logger> s_CoreLogger;
    static std::shared_ptr<spdlog::logger> s_ClientLogger;

public:
    static void init();

    inline static std::shared_ptr<spdlog::logger> &getCoreLogger() {
        return s_CoreLogger;
    }
    inline static std::shared_ptr<spdlog::logger> &getClientLogger() {
        return s_ClientLogger;
    }
};

} // namespace Smedja

// clang-format off
// Engine log macros
#define SD_CORE_TRACE(...)    ::Smedja::Log::getCoreLogger()->trace(__VA_ARGS__)
#define SD_CORE_INFO(...)     ::Smedja::Log::getCoreLogger()->info(__VA_ARGS__)
#define SD_CORE_WARN(...)     ::Smedja::Log::getCoreLogger()->warn(__VA_ARGS__)
#define SD_CORE_ERROR(...)    ::Smedja::Log::getCoreLogger()->error(__VA_ARGS__)
#define SD_CORE_CRITICAL(...) ::Smedja::Log::getCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define SD_TRACE(...)         ::Smedja::Log::getClientLogger()->trace(__VA_ARGS__)
#define SD_INFO(...)          ::Smedja::Log::getClientLogger()->info(__VA_ARGS__)
#define SD_WARN(...)          ::Smedja::Log::getClientLogger()->warn(__VA_ARGS__)
#define SD_ERROR(...)         ::Smedja::Log::getClientLogger()->error(__VA_ARGS__)
#define SD_CRITICAL(...)      ::Smedja::Log::getClientLogger()->critical(__VA_ARGS__)
// clang-format on
