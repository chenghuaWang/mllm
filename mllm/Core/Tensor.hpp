/**
 * @file Tensor.hpp
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
#include "mllm/Core/TensorImpl.hpp"
#include <cstdint>
#include <initializer_list>
#include <memory>
#include <vector>

namespace mllm {

enum TensorSliceIndexSymbol : int32_t {
  All = -100000000,
  Auto = -100000001,
};

struct TensorSliceDescriptor {
  TensorSliceDescriptor() = default;
  TensorSliceDescriptor(const std::initializer_list<int32_t>& l);

  bool is_single_index = false;
  int32_t single_index = 0;
  int32_t start = 0;
  int32_t end = 0;
  int32_t step = 1;
};

class TensorSliceIndex {
 public:
  TensorSliceIndex(const std::vector<TensorSliceDescriptor>& indicies);

  inline std::vector<TensorSliceDescriptor>::iterator begin() noexcept { return indicies_.begin(); }

  inline std::vector<TensorSliceDescriptor>::iterator end() noexcept { return indicies_.end(); }

  inline std::vector<TensorSliceDescriptor>::const_iterator begin() const noexcept {
    return indicies_.begin();
  }

  inline std::vector<TensorSliceDescriptor>::const_iterator end() const noexcept {
    return indicies_.end();
  }

  inline size_t size() const { return indicies_.size(); }

 private:
  std::vector<TensorSliceDescriptor> indicies_;
};

class Tensor {
 public:
  template<typename T>
  inline T& operator[](const TensorSliceIndex& index) {
    auto ptr = impl_->rawPtr<T>();
    return ptr[offset(index)];
  }

  inline Tensor operator[](const TensorSliceIndex& index) {}

  size_t offset(const std::initializer_list<int32_t>& l) const;

  // only support single index type for TensorSliceDescriptor in TensorSliceIndex
  size_t offset(const TensorSliceIndex& index) const;

  inline DataTypes dtype() const { return impl_->dtype; }

  inline DeviceTypes device() const { return impl_->device; }

  Tensor& to(const DeviceTypes& device_type);

  Tensor& to(const DataTypes& data_type);

 private:
  std::vector<int32_t> stride_;
  std::vector<int32_t> shape_;

  // all data is in TensorImpl
  // such as: array, quantization shift and scale values.
  std::shared_ptr<TensorImpl> impl_;
};

}  // namespace mllm