/**
 * @file Tensor.cpp
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
#include "mllm/Core/Tensor.hpp"
#include "mllm/Utils/Common.hpp"
#include "mllm/Utils/Log.hpp"

namespace mllm {

TensorSliceDescriptor::TensorSliceDescriptor(const std::initializer_list<int32_t>& l) {
  switch (l.size()) {
    case 0: {
      start = TensorSliceIndexSymbol::All;
      break;
    }
    case 1:
      if (*l.begin() == All) {
        start = TensorSliceIndexSymbol::All;
      } else {
        single_index = *l.begin();
        is_single_index = true;
      }
      break;
    case 2:
      start = *l.begin();
      end = *(l.begin() + 1);
      break;
    case 3:
      start = *l.begin();
      end = *(l.begin() + 1);
      step = *(l.begin() + 2);
      break;
    default:
      MLLM_FATAL_EXIT(ExitCode::kSliceOB,
                      "SliceDescriptor only support 1, 2 or 3 as inputs. [single "
                      "index] or [start, end, step(optional)]");
  }
}

TensorSliceIndex::TensorSliceIndex(const std::vector<TensorSliceDescriptor>& indicies)
    : indicies_(indicies) {
  // check legalization
  for (auto& descriptor : indicies_) {
    // 1. check `All`
    if (descriptor.start == TensorSliceIndexSymbol::All && descriptor.end != 0) {
      MLLM_WARN("Find `All` in TensorSliceIndex.start, but TensorSliceIndex.end is not 0. Reset "
                "TensorSliceIndex.end to 0");
      descriptor.end = 0;
    }

    // 2. check `Auto`
    if (descriptor.start == TensorSliceIndexSymbol::Auto
        && descriptor.end == TensorSliceIndexSymbol::Auto) {
      MLLM_WARN("Find `Auto` in TensorSliceIndex.start and TensorSliceIndex.end, Reset "
                "TensorSliceIndex.start to `All` and TensorSliceIndex.end to 0");
      descriptor.start = TensorSliceIndexSymbol::All;
      descriptor.end = 0;
    }
  }
}

size_t Tensor::offset(const std::initializer_list<int32_t>& l) const {
  MLLM_RT_ASSERT_EQ(stride_.size(), l.size());

  auto offsets_array = l.begin();
  size_t ret = 0;
  for (size_t i = 0; i < l.size(); ++i) { ret += stride_[i] * offsets_array[i]; }

  return ret;
}

size_t Tensor::offset(const TensorSliceIndex& index) const {
  MLLM_RT_ASSERT_EQ(stride_.size(), index.size());
  size_t ret = 0;
  for (size_t i = 0; i < index.size(); ++i) {
    ret += stride_[i] * (index.begin() + i)->single_index;
  }
  return ret;
}

Tensor& Tensor::to(const DeviceTypes& device_type) {
  if (device_type == device()) { return *this; }

  // TODO
  // send op to vm to do some memory transfer between devices

  impl_->device = device_type;
  return *this;
}

Tensor& Tensor::to(const DataTypes& data_type) {
  if (data_type == dtype()) { return *this; }

  // TODO
  // send op to vm to do some data cast

  impl_->dtype = data_type;
  return *this;
}

}  // namespace mllm
