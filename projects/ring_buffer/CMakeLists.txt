add_library(ring_buffer INTERFACE)
add_library(learning::ring_buffer ALIAS ring_buffer)

target_include_directories(
    ring_buffer
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
