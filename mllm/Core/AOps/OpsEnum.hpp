/**
 * @file OpsEnum.hpp
 * @author chenghua Wang (chenghua.wang.edu@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-01-19
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <cstdint>
namespace mllm {

enum class OpType : uint16_t {
  kStart = 0,

  // elementwise
  kAdd,

  kEnd,
};

}