#pragma once

#include <cstdint>
#include <iostream>
#include <format>
#include <string_view>

namespace Jupiter {
namespace Core {

enum class LogLevel : uint16_t { Trace = 0, Info, Warning, Error, Fatal, None };

class Logger {
public:
  static void SetLevel(LogLevel level) { s_currentLevel = level; }
  static LogLevel GetLevel() { return s_currentLevel; }

  template <typename... Args>
  static void Log(LogLevel level, std::string_view prefix,
                  std::string_view color, std::format_string<Args...> fmt,
                  Args &&...args) {
    if (level < s_currentLevel)
      return;

    std::string message = std::format(fmt, std::forward<Args>(args)...);
    std::cout << color << "[" << prefix << "] " << message << "\033[0m"
              << std::endl;
  }

private:
  inline static LogLevel s_currentLevel = LogLevel::Trace;
};

} // namespace Core
} // namespace Jupiter

#define J_COL_GRAY "\033[90m"
#define J_COL_GREEN "\033[32m"
#define J_COL_YELLOW "\033[33m"
#define J_COL_RED "\033[31m"
#define J_COL_FATAL "\033[41m\033[37m"

#ifdef J_DEBUG
#define J_INFO(...)                                                            \
  ::Jupiter::Core::Logger::Log(::Jupiter::Core::LogLevel::Info, "INFO",        \
                               J_COL_GREEN, __VA_ARGS__)
#define J_WARN(...)                                                            \
  ::Jupiter::Core::Logger::Log(::Jupiter::Core::LogLevel::Warning, "WARN",     \
                               J_COL_YELLOW, __VA_ARGS__)
#define J_ERROR(...)                                                           \
  ::Jupiter::Core::Logger::Log(::Jupiter::Core::LogLevel::Error, "ERROR",      \
                               J_COL_RED, __VA_ARGS__)
#define J_FATAL(...)                                                           \
  ::Jupiter::Core::Logger::Log(::Jupiter::Core::LogLevel::Fatal, "FATAL",      \
                               J_COL_FATAL, __VA_ARGS__)
#else
#define J_INFO(...)
#define J_WARN(...)
#define J_ERROR(...)
#define J_FATAL(...)
#endif
