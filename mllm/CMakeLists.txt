file(GLOB_RECURSE MLLM_CORE_SRC ${CMAKE_CURRENT_LIST_DIR}/*.cpp)
add_library(MllmCore SHARED ${MLLM_CORE_SRC})
target_include_directories(MllmCore PUBLIC ${MLLM_INCLUDE_DIR})
target_link_libraries(MllmCore PUBLIC fmt::fmt-header-only)
