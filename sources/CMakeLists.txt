set(CURVE_LIB "${CMAKE_CURRENT_SOURCE_DIR}/curve_test.cpp" "../headers/curve_test.h")

add_library(curves SHARED ${CURVE_LIB})
target_include_directories(curves PUBLIC "../headers/")