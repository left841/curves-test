cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project("curves_test")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/")

find_package(OpenMP REQUIRED)
if(NOT OpenMP_CXX_FOUND)
    message(FATAL_ERROR "openmp not found")
endif(NOT OpenMP_CXX_FOUND)

set(CURVE_LIB "${CMAKE_CURRENT_SOURCE_DIR}/sources/curve_test.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/headers/curve_test.h")

add_library(curves SHARED ${CURVE_LIB})
target_include_directories(curves PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/headers/")

add_executable(sample "${CMAKE_CURRENT_SOURCE_DIR}/samples/usage_sample.cpp")
target_include_directories(sample PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/headers/" ${OpenMP_INCLUDE_DIRS})
target_link_libraries(sample curves OpenMP::OpenMP_CXX)

enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        main
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)
add_executable(testing "${CMAKE_CURRENT_SOURCE_DIR}/test/testing.cpp")

target_include_directories(testing PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/headers/")
target_link_libraries(testing curves GTest::GTest)

add_test(NAME base_test COMMAND testing WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
