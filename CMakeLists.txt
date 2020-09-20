project (cpp-scope-guard)
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

add_executable(
    scope-guard-test
    scope-guard-test.cpp)

set_property(
    TARGET scope-guard-test
    PROPERTY CXX_STANDARD 20)
