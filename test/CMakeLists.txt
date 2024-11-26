cmake_minimum_required(VERSION 3.16)
project(AdditionTest LANGUAGES CXX C)

# Download googletest and make it available for make.
# This step can be separated into a top level CMakeLists.txt which calls multiple tests
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

# enable testing and googletest in cmake
enable_testing()
include(GoogleTest)

# Create a test executable 
add_executable(bq_test "")

# O0 and ggdb compile flags for debugging
target_compile_options(bq_test PUBLIC -ggdb -g3 -O0 -Wall -Werror)

# Specify source files to the target executable
target_sources(bq_test PRIVATE
    bq_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../biquad.c
)

# Specify include path directories to the target executable 
target_include_directories(bq_test PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/../
)

# Specify libraries used bythe target executable 
target_link_libraries(bq_test
 PRIVATE
  GTest::GTest )

# Add the test which can be discovered by test framework
gtest_discover_tests(bq_test)
