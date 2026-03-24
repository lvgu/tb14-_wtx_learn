cmake_minimum_required(VERSION 3.20)

project(AlogrithmsLearning LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)

add_subdirectory(projects/ring_buffer)
add_subdirectory(projects/bst)
add_subdirectory(projects/test_registry)
