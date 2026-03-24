# AlogrithmsLearning

A modular C++ learning workspace where each topic is a small subproject.

## Layout

```text
AlogrithmsLearning/
  projects/
    ring_buffer/   # circular buffer library
    bst/           # binary search tree library
    test_registry/ # tiny testing framework + registered tests
  docs/
```

## Build

```powershell
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Add New Subprojects

1. Create a new folder under `projects/`, for example `projects/graph`.
2. Add a `CMakeLists.txt` in that folder.
3. Add `add_subdirectory(projects/graph)` in the root `CMakeLists.txt`.
4. Put examples/tests next to the subproject or register tests in `test_registry`.
