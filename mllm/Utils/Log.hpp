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

#include <fmt/core.h>

namespace mllm {

enum class LogLevel {
  kInfo = 0,
  kWarn = 1,
  kError = 2,
  kFatal = 3,
};

extern LogLevel LOG_LEVEL;

} // namespace mllm

#define MLLM_INFO(...)                                                         \
  if (mllm::LOG_LEVEL <= mllm::LogLevel::kInfo) {                              \
    fmt::print("[INFO] {}:{} {}\n", __FILE__, __LINE__,                        \
               fmt::format(__VA_ARGS__));                                      \
  }
