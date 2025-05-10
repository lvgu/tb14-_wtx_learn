
cmake_minimum_required(VERSION 3.25)
project(wtx_test VERSION 1.0)


# 设置 C++ 标准（如 C++20）
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置可执行文件的输出路径（如 bin 目录）
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

cmake_policy(SET CMP0074 NEW)
# 配置Boost路径
set(Boost_ROOT "D:/wtx_dev_workspace/boost_install")  # Boost安装路径
set(BOOST_INCLUDEDIR "D:/wtx_dev_workspace/boost_install/include")  # Boost安装路径
set(BOOST_LIBRARYDIR "D:/wtx_dev_workspace/boost_install/lib")  # Boost安装路径
message(STATUS "Boost root : ${Boost_ROOT}")

set(Boost_USE_STATIC_LIBS ON)       # 使用静态库
set(Boost_USE_MULTITHREADED ON)     # 多线程支持
set(Boost_USE_STATIC_RUNTIME OFF)   # 使用动态运行时（可选）

# 查找Boost组件
find_package(Boost REQUIRED COMPONENTS filesystem system
PATHS ${Boost_ROOT})


# 在 src 目录下的 CMakeLists.txt 中添加可执行文件
# src/CMakeLists.txt 内容：
add_executable(wtx_test main.cpp)

# 链接Boost库
target_include_directories(wtx_test PRIVATE ${BOOST_INCLUDEDIR})
target_link_libraries(wtx_test ${Boost_LIBRARIES})

# 添加源文件目录
#add_subdirectory(src)

