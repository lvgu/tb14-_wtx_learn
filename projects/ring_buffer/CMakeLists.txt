# 环形缓冲区是纯头文件库，用 INTERFACE 目标暴露 include 目录
add_library(ring_buffer INTERFACE)
add_library(learning::ring_buffer ALIAS ring_buffer)

# 对外公开头文件路径，供其他目标 include
target_include_directories(
    ring_buffer
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
