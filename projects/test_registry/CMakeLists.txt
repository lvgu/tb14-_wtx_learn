# 测试程序：把测试入口和测试用例都编译进一个可执行文件
add_executable(
    test_registry
    src/main.cpp
    tests/ring_buffer_tests.cpp
    tests/bst_tests.cpp
)

# 测试框架头文件路径
target_include_directories(
    test_registry
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 链接被测库
target_link_libraries(
    test_registry
    PRIVATE
        learning::ring_buffer
        learning::bst
)

# 向 CTest 注册该测试可执行程序
if(BUILD_TESTING)
    add_test(NAME learning_registered_tests COMMAND test_registry)
endif()
