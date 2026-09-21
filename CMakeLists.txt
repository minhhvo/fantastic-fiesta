# /workspace/CMakeLists.txt

cmake_minimum_required(VERSION 3.20)
project(Monorepo_CPP_Engine CXX)

# 1. Global compiler settings (MUST come before targets so they inherit C++20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 2. Global OS Macros 
if(WIN32)
    add_compile_definitions(OS_WINDOWS=1)
elseif(UNIX AND NOT APPLE)
    add_compile_definitions(OS_LINUX=1)
endif()

# Enable testing globally at the root
enable_testing()

# 3. Internal Dev-dependencies Setup 
add_library(TimeIt STATIC ${CMAKE_SOURCE_DIR}/tests/utils/TimeIt.cpp)
target_include_directories(TimeIt PUBLIC ${CMAKE_SOURCE_DIR}/tests/utils)

add_library(ConsoleApp STATIC ${CMAKE_SOURCE_DIR}/tests/utils/consoleApp.cpp)
target_include_directories(ConsoleApp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/tests/utils)


# 4. GoogleTest Setup
include(cmake/testing_deps.cmake)

# 5. Register nested modules (MUST come before linking them to root tests)
add_subdirectory(packages/algebra/src/algebra/.cpp)

# 6. Create root test executable 
# (Safe to link Calculator now because the subdirectory was loaded above)
add_executable(my_tests test_main.cpp)
target_link_libraries(my_tests PRIVATE Calculator GTest::gtest_main)

# --- Helpers for Boost third-party libs ---
# find_package(Boost REQUIRED)
# target_link_libraries(algebra_test PRIVATE Boost::boost)
# target_include_directories(algebra_test PRIVATE ${Boost_INCLUDE_DIRS})