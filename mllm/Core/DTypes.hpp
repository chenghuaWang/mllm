/**
 * @file DTypes.hpp
 * @author chenghua Wang (chenghua.wang.edu@gmail.com)
 * @brief
 * @version 0.1
 * @date 2025-01-17
 *
 * @copyright Copyright (c) 2025
 *
 */
#pragma once

#include <cstdint>
#include <string>

namespace mllm {

enum class DataTypes : int32_t {
  // Normal
  kStart = 0,
  kInt4,
  kInt8,
  kFP4,
  kFP8,
  kFP16,
  kFP32,
  kFP64,

  // Per-Tensor(PT) Quantization
  // symmetry: Sym
  // asymmetric: Asy
  kPT_Int4_Sym,
  kPT_Int4_Asy,
  kPT_Int8_Sym,
  kPT_Int8_Asy,

  // Per-Channel(PC) Quantization
  kPC_Int4_Sym,
  kPC_Int4_Asy,
  kPC_Int8_Sym,
  kPC_Int8_Asy,

  // Per-Group(PG) Quantization

  kEnd,
};

inline std::string getDataTypeName(DataTypes type) {
  switch (type) {
    case DataTypes::kStart: return "Start";
    case DataTypes::kInt4: return "Int4";
    case DataTypes::kInt8: return "Int8";
    case DataTypes::kFP4: return "FP4";
    case DataTypes::kFP8: return "FP8";
    case DataTypes::kFP16: return "FP16";
    case DataTypes::kFP32: return "FP32";
    case DataTypes::kFP64: return "FP64";
    case DataTypes::kPT_Int4_Sym: return "Per-Tensor Int4 (Symmetric)";
    case DataTypes::kPT_Int4_Asy: return "Per-Tensor Int4 (Asymmetric)";
    case DataTypes::kPT_Int8_Sym: return "Per-Tensor Int8 (Symmetric)";
    case DataTypes::kPT_Int8_Asy: return "Per-Tensor Int8 (Asymmetric)";
    case DataTypes::kPC_Int4_Sym: return "Per-Channel Int4 (Symmetric)";
    case DataTypes::kPC_Int4_Asy: return "Per-Channel Int4 (Asymmetric)";
    case DataTypes::kPC_Int8_Sym: return "Per-Channel Int8 (Symmetric)";
    case DataTypes::kPC_Int8_Asy: return "Per-Channel Int8 (Asymmetric)";
    case DataTypes::kEnd: return "End";
    default: return "Unknown DataType";
  }
}

}  // namespace mllm