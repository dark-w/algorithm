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

include(GoogleTest)
gtest_discover_tests(test_insert_sort)
gtest_discover_tests(test_merge_sort)
gtest_discover_tests(test_find_max_subarray)
