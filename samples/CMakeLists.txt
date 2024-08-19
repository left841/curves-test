add_executable(sample "${CMAKE_CURRENT_SOURCE_DIR}/usage_sample.cpp")
target_include_directories(sample PUBLIC "../headers/" ${OpenMP_INCLUDE_DIRS})
target_link_libraries(sample curves OpenMP::OpenMP_CXX)