/**
 * @file TensorImpl.hpp
 * @author chenghua Wang (chenghua.wang.edu@gmail.com)
 * @author yirongjie
 * @author lx200916
 * @author oreomaker
 * @author liang1232018
 * @brief
 * @version 0.1
 * @date 2025-01-17
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include "mllm/Core/DTypes.hpp"
#include "mllm/Core/DeviceTypes.hpp"

namespace mllm {

class TensorImpl {
 public:
  template<typename T>
  inline T* rawPtr() {
    return static_cast<T*>(raw_ptr);
  }
  void* raw_ptr;

  DataTypes dtype = DataTypes::kFP32;
  DeviceTypes device = DeviceTypes::kHost;
};

}  // namespace mllm