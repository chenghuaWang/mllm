cmake_minimum_required(VERSION 3.21)
project(mllm C CXX ASM)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(MLLM_ENABLE_TEST "Enable mllm test" ON)

message(STATUS "CXX Compiler=${CMAKE_CXX_COMPILER_ID}")
message(STATUS "CXX Compiler version=${CMAKE_CXX_COMPILER_VERSION}")

set(MLLM_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(third_party/fmt EXCLUDE_FROM_ALL)

add_subdirectory(mllm)

if(MLLM_ENABLE_TEST)
    add_subdirectory(third_party/googletest EXCLUDE_FROM_ALL)
    add_subdirectory(tests)
endif()
