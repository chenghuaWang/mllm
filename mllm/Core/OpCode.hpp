/**
 * @file OpCode.hpp
 * @author chenghua Wang (chenghua.wang.edu@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-01-18
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include "mllm/Core/DeviceTypes.hpp"
#include "mllm/Core/AOps/OpsEnum.hpp"

namespace mllm {

// uint16_t: device
// uint16_t: op
class OpCode {
 public:
  OpCode() = default;
  OpCode(DeviceTypes device, OpType op) : inst_code_(((uint32_t)device) << 16 | (uint16_t)op) {}

  inline uint32_t inst() const { return inst_code_; }

 private:
  uint32_t inst_code_;
};

}  // namespace mllm