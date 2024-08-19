FetchContent_Declare(googletest GIT_REPOSITORY https://github.com/google/googletest.git GIT_TAG main)
FetchContent_MakeAvailable(googletest)

add_executable(testing "${CMAKE_CURRENT_SOURCE_DIR}/testing.cpp")
target_include_directories(testing PUBLIC "../headers/")
target_link_libraries(testing curves gtest_main)

add_test(NAME base_test COMMAND testing WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")