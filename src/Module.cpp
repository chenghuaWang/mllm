//
// Created by Rongjie Yi on 2024/1/28 0028.
//

#include "Module.hpp"

namespace mllm {

map<BackendType, Backend*> Module::backends;
AbstructLoader *Module::loader;
int Module::listIdx;
int Module::runlistIdx;
// TensorStatus Tensor::tensor_status;
bool Module::doLoad = false;
} // namespace mllm