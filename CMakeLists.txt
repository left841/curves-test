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

set(CURVE_LIB "${CMAKE_CURRENT_SOURCE_DIR}/sources/curve_test.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/headers/curve_test.h")

add_library(curves SHARED ${CURVE_LIB})
target_include_directories(curves PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/headers/")

add_executable(sample "${CMAKE_CURRENT_SOURCE_DIR}/samples/usage_sample.cpp")
target_include_directories(sample PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/headers/")
target_link_libraries(sample curves)
