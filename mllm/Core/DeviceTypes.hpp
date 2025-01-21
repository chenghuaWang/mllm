/**
 * @file DeviceTypes.hpp
 * @author chenghua Wang (chenghua.wang.edu@gmail.com)
 * @brief We support the edge devices which have one cpu/gpu/npu etc. Multi-GPU in an one device is
 * not supported yet.
 * @version 0.1
 * @date 2025-01-18
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <cstdint>
#include <string>

namespace mllm {

enum class DeviceTypes : uint16_t {
  kStart = 0,
  kHost,
  kOpenCL,
  kQnn,
  kEnd,
};

inline std::string getDeviceTypeName(DeviceTypes type) {
  switch (type) {
    case DeviceTypes::kStart: return "Start";
    case DeviceTypes::kHost: return "Host";
    case DeviceTypes::kOpenCL: return "OpenCL";
    case DeviceTypes::kQnn: return "Qnn";
    case DeviceTypes::kEnd: return "End";
    default: return "Unknown DeviceType";
  }
}

}  // namespace mllm