# /workspace/packages/algebra/src/algebra/.cpp/
# CMakeLists.txt

set(TARGET_PROJECT "Calculator")
project(${TARGET_PROJECT})

# STEP 1: The "Dry" Compile
# Using an OBJECT library syntax-checks and compiles the source files without the overhead of linking.
add_library(${TARGET_PROJECT} STATIC MathLibrary.cpp Calculator.cpp)
target_include_directories(${TARGET_PROJECT} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# STEP 2: The Compiled Binary
# Compiles the test executable completely independently from the same source files.
add_executable(${TARGET_PROJECT}_test Calculator.cpp)
target_link_libraries(
    ${TARGET_PROJECT}_test PRIVATE ${TARGET_PROJECT} GTest::gtest_main
)

# (Optional) AUTO-RUN: Execute the test automatically if compilation succeeds
add_custom_command(TARGET ${TARGET_PROJECT}_test POST_BUILD
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_PROJECT}_test
)