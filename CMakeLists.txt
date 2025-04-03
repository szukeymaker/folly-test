cmake_minimum_required(VERSION 3.30)
project(folly_test CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(folly_test
    test_asyncscope.cc)

target_link_libraries(folly_test
    PRIVATE
    folly
    glog
    gflags
    double-conversion
    boost_context
    event
    fmt
    unwind)
