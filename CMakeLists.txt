# /workspace/CMakeLists.txt

cmake_minimum_required(VERSION 3.20)
project(Monorepo_CPP_Engine CXX)

project(Calculator)
enable_testing()


# 1. Global compiler settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 2. Global OS Macros (Applies to all subdirectories automatically)
if(WIN32)
    add_compile_definitions(OS_WINDOWS=1)
elseif(UNIX AND NOT APPLE)
    add_compile_definitions(OS_LINUX=1)
endif()

# 3. GoogleTest Setup
include(cmake/testing_deps.cmake)

# 4. Create root test executable MUST happen before linking
add_executable(my_tests test_main.cpp)
target_link_libraries(my_tests PRIVATE Calculator GTest::gtest_main)

# 5. Register the nested module
add_subdirectory(packages/algebra/src/algebra/.cpp)

# --- Helpers for Boost third-party libs ---
# find_package(Boost REQUIRED)
# target_link_libraries(algebra_test PRIVATE Boost::boost)
# target_include_directories(algebra_test PRIVATE ${Boost_INCLUDE_DIRS})