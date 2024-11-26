project(Google_tests)

add_subdirectory(lib)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(Google_Tests_run test1.cpp)

target_link_libraries(Google_Tests_run calculator_lib)
target_link_libraries(Google_Tests_run gtest gtest_main)

add_test(runUnitTests Google_Tests_run)