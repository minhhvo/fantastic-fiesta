# /workspace/projects/CMakeLists.txt
cmake_minimum_required(VERSION 3.20)

# 1. Define the global project (Fixes the CMake warning)
project(Monorepo_CPP_Engine CXX)

# 2. Global compiler settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 3. Register the nested module
# This path must be relative to this root file
add_subdirectory(packages/algebra/src/algebra/.cpp)

# --- Helpers for Boost third-party libs ---
# # --- Find Boost package ---
# find_package(Boost REQUIRED)
# # --- Link it to your target ---
# target_link_libraries(algebra_test PRIVATE Boost::boost)
# target_include_directories(algebra_test PRIVATE ${Boost_INCLUDE_DIRS})