# 二叉搜索树是纯头文件库，用 INTERFACE 目标暴露 include 目录
add_library(bst INTERFACE)
add_library(learning::bst ALIAS bst)

# 对外公开头文件路径，供其他目标 include
target_include_directories(
    bst
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
