/**
 * @file Log.hpp
 * @author chenghua Wang (chenghua.wang.edu@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-01-15
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <fmt/color.h>
#include <fmt/core.h>

namespace mllm {

enum class LogLevel {
  kInfo = 0,
  kWarn = 1,
  kError = 2,
  kFatal = 3,
  kAssert = 4,
};

extern LogLevel LOG_LEVEL;

}  // namespace mllm

#define MLLM_INFO(...)                                                       \
  if (mllm::LOG_LEVEL <= mllm::LogLevel::kInfo) {                            \
    fmt::print(fg(fmt::color::green) | fmt::emphasis::bold, "[INFO]");       \
    fmt::print(" {}:{} {}\n", __FILE__, __LINE__, fmt::format(__VA_ARGS__)); \
  }

#define MLLM_WARN(...)                                                        \
  if (mllm::LOG_LEVEL <= mllm::LogLevel::kWarn) {                             \
    fmt::print(fg(fmt::color::green_yellow) | fmt::emphasis::bold, "[WARN]"); \
    fmt::print(" {}:{} {}\n", __FILE__, __LINE__, fmt::format(__VA_ARGS__));  \
  }

#define MLLM_WARN_EXIT(code, ...)                                             \
  if (mllm::LOG_LEVEL <= mllm::LogLevel::kWarn) {                             \
    fmt::print(fg(fmt::color::green_yellow) | fmt::emphasis::bold, "[WARN]"); \
    fmt::print(" {}:{} {}\n", __FILE__, __LINE__, fmt::format(__VA_ARGS__));  \
  }                                                                           \
  exit(code)

#define MLLM_ERROR(...)                                                      \
  if (mllm::LOG_LEVEL <= mllm::LogLevel::kError) {                           \
    fmt::print(fg(fmt::color::red) | fmt::emphasis::bold, "[ERROR]");        \
    fmt::print(" {}:{} {}\n", __FILE__, __LINE__, fmt::format(__VA_ARGS__)); \
  }

#define MLLM_ERROR_EXIT(code, ...)                                           \
  if (mllm::LOG_LEVEL <= mllm::LogLevel::kError) {                           \
    fmt::print(fg(fmt::color::red) | fmt::emphasis::bold, "[ERROR]");        \
    fmt::print(" {}:{} {}\n", __FILE__, __LINE__, fmt::format(__VA_ARGS__)); \
  }                                                                          \
  exit(code)

#define MLLM_FATAL_EXIT(code, ...)                                           \
  if (mllm::LOG_LEVEL <= mllm::LogLevel::kFatal) {                           \
    fmt::print(fg(fmt::color::red) | fmt::emphasis::bold, "[FATAL]");        \
    fmt::print(" {}:{} {}\n", __FILE__, __LINE__, fmt::format(__VA_ARGS__)); \
  }                                                                          \
  exit(code)

#define MLLM_ASSERT_EXIT(code, ...)                                          \
  if (mllm::LOG_LEVEL <= mllm::LogLevel::kAssert) {                          \
    fmt::print(fg(fmt::color::red) | fmt::emphasis::bold, "[ASSERT]");       \
    fmt::print(" {}:{} {}\n", __FILE__, __LINE__, fmt::format(__VA_ARGS__)); \
  }                                                                          \
  exit(code)
