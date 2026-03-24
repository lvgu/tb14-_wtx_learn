cmake_minimum_required(VERSION 3.20)

# 顶层工程：统一管理所有学习子项目
project(AlogrithmsLearning LANGUAGES CXX)

# 全局 C++ 编译选项
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 启用 CTest，便于统一跑测试
include(CTest)

# 注册各个子项目
add_subdirectory(projects/ring_buffer)
add_subdirectory(projects/bst)
add_subdirectory(projects/test_registry)
