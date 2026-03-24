add_executable(
    test_registry
    src/main.cpp
    tests/ring_buffer_tests.cpp
    tests/bst_tests.cpp
)

target_include_directories(
    test_registry
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(
    test_registry
    PRIVATE
        learning::ring_buffer
        learning::bst
)

if(BUILD_TESTING)
    add_test(NAME learning_registered_tests COMMAND test_registry)
endif()
