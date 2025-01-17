add_executable(Mllm-Utils-LogTest LogTest.cpp)
target_link_libraries(Mllm-Utils-LogTest PRIVATE gtest_main MllmCore)
target_include_directories(Mllm-Utils-LogTest PRIVATE ${MLLM_INCLUDE_DIR})
include(GoogleTest)

gtest_discover_tests(Mllm-Utils-LogTest)
