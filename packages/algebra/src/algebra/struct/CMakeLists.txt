# /workspace/projects/packages/algebra/src/algebra/struct/CMakeLists.txt

cmake_minimum_required(VERSION 3.25)
project(algebra-build-test)
set(CMAKE_CXX_STANDARD 20)

# 1. Create a standalone executable for isolated testing
add_executable(algebra_test main.cpp shape.cpp)


# 2. Tell the compiler where to find shape.hpp
target_include_directories(algebra_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})