/**
 * @file XpInterface.hpp
 * @author Chenghua Wang (chenghua.wang.edu@gmail.com)
 * @version 0.1
 * @date 2024-10-09
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

#include "Tensor.hpp"
#include "xnnpack.h"
#include "backends/xnnpack/XnnpackBackend.hpp"
#include "backends/xnnpack/Utils/Logger.hpp"
#include <memory>
#include <array>

namespace mllm::xnnpack {

enum class XpTensorType : uint32_t {
    Normal = 0,
    ExternalInput = 1,
    ExternalOutput = 2,
};

template <typename T>
struct XpTensorDefineInterface {
    void tryDefineAllXpTensors(XnnpackBackend *xpb, std::vector<std::shared_ptr<Tensor>> &ts) {
        for (auto &t : ts) {
            XpTensorType _t;
            switch (t->xnnTensorType()) {
            case TensorType::INPUT_TENSOR:
                _t = XpTensorType::ExternalInput;
                break;
            case TensorType::OUTPUT_TENSOR:
                _t = XpTensorType::ExternalOutput;
                break;
            case TensorType::NORMAL_TENSOR:
                _t = XpTensorType::Normal;
                break;
            }

            defineXpTensor(xpb, t.get(), _t);
        }
    }

    void tryDefineAllXpTensors(XnnpackBackend *xpb, std::vector<Tensor *> &ts) {
        for (auto &t : ts) {
            XpTensorType _t;
            switch (t->xnnTensorType()) {
            case TensorType::INPUT_TENSOR:
                _t = XpTensorType::ExternalInput;
                break;
            case TensorType::OUTPUT_TENSOR:
                _t = XpTensorType::ExternalOutput;
                break;
            case TensorType::NORMAL_TENSOR:
                _t = XpTensorType::Normal;
                break;
            }

            defineXpTensor(xpb, t, _t);
        }
    }

    void defineXpTensor(XnnpackBackend *xpb, Tensor *t, XpTensorType ttype) {
        if (t->uuid() != XNN_INVALID_VALUE_ID) return;

        auto xp_dtype = XnnpackBackend::mllmDType2XnnDType(t->dtype());

        xnn_status status;
        std::array<size_t, 4> dims = {0, 0, 0, 0};
        dims[0] = t->batch();
        dims[1] = t->head();
        dims[2] = t->sequence();
        dims[3] = t->dimension();

        uint32_t flags;
        uint32_t external_id = XNN_INVALID_VALUE_ID;

        switch (ttype) {
        case XpTensorType::Normal:
            flags = XNN_INVALID_VALUE_ID;
            break;
        case XpTensorType::ExternalInput:
            flags = XNN_VALUE_FLAG_EXTERNAL_INPUT;
            external_id = xpb->getNewEXternalId();
            break;
        case XpTensorType::ExternalOutput:
            flags = XNN_VALUE_FLAG_EXTERNAL_OUTPUT;
            external_id = xpb->getNewEXternalId();
            break;
        }

        switch (xp_dtype) {
        case xnn_datatype_fp32: {
            status = xnn_define_tensor_value(
                xpb->getXnnSubgraph(), xp_dtype,
                dims.size(), dims.data(),
                /*data=*/nullptr,
                external_id, flags, &t->uuid());
        }
        default:
            break;
        }

        switch (ttype) {
        case XpTensorType::Normal:
            break;
        case XpTensorType::ExternalInput:
        case XpTensorType::ExternalOutput:
            xpb->registerExternalValue(t->uuid(), xnn_external_value{.id = t->uuid(), .data = t->rawHostPtr()});
            xpb->registerUuidTensor(t->uuid(), t);
            break;
        }

        if (status != xnn_status_success) {
            Log::error("xnnpack backend defineXpTensor Error");
            exit(-1);
        }
    }
};

} // namespace mllm::xnnpack