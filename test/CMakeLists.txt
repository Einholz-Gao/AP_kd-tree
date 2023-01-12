cmake_minimum_required(VERSION 3.1)
project(kd-tree_test) #name of your project

add_subdirectory(googletest) # add googletest subdirectory

include_directories(googletest/include) # this is so we can #include <gtest/gtest.h>

add_executable(kd-search-test kd-search-test.cpp) # add this executable

target_link_libraries(kd-search-test PRIVATE gtest) # link google test to this executable

