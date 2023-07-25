cmake_minimum_required(VERSION 3.14)
project(my_project)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# 设置 Eigen3 的路径
include_directories(./lib/eigen-3.4.0)

enable_testing()
include_directories(${gtest_SOURCE_DIR}/include)

add_executable(
  test_insert_sort
  test/test_insert_sort.cc
  src/insert_sort.cc
)

add_executable(
  test_merge_sort
  test/test_merge_sort.cc
  src/merge_sort.cc
)

add_executable(
  test_find_max_subarray
  test/test_find_max_subarray.cc
  src/find_max_subarray.cc
)

add_executable(
  test_matrix
  test/test_matrix.cc
  src/matrix.cc
)

add_executable(
  test_fib
  test/test_fib.cc
  src/fib.cc
  src/matrix.cc
)

add_executable(
  test_fft
  test/test_fft.cc
  src/fft.cc
  src/matrix.cc
  src/complex.cc
)

add_executable(
  test_quick_sort
  test/test_quick_sort.cc
  src/quick_sort.cc
)

target_link_libraries(
  test_insert_sort
  GTest::gtest_main
)

target_link_libraries(
  test_merge_sort
  GTest::gtest_main
)

target_link_libraries(
  test_find_max_subarray
  GTest::gtest_main
)

target_link_libraries(
  test_matrix
  GTest::gtest_main
)

target_link_libraries(
  test_fib
  GTest::gtest_main
)

target_link_libraries(
  test_fft
  GTest::gtest_main
)

target_link_libraries(
  test_quick_sort
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_insert_sort)
gtest_discover_tests(test_merge_sort)
gtest_discover_tests(test_find_max_subarray)
gtest_discover_tests(test_matrix)
gtest_discover_tests(test_fib)
gtest_discover_tests(test_fft)
gtest_discover_tests(test_quick_sort)
