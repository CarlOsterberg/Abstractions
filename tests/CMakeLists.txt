
add_executable(matrix_tests matrix_tests.cpp)

target_link_libraries(matrix_tests
        PRIVATE
        gtest
        gtest_main
        matrices
)

include(GoogleTest)
gtest_discover_tests(matrix_tests)
