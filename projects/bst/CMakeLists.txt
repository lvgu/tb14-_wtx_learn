add_library(bst INTERFACE)
add_library(learning::bst ALIAS bst)

target_include_directories(
    bst
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
