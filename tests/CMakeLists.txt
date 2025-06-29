# tests/CMakeLists.txt

add_executable(matrix_addition addition.cpp)

target_link_libraries(matrix_addition
        PRIVATE
        gtest
        gtest_main
        matrices
)

include(GoogleTest)
gtest_discover_tests(matrix_addition)
