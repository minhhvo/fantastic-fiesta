# /workspace/cmake/
# algebra.cmake

set(TARGET_PROJECT "algebra")

# STEP 1: The "Dry" Compile
# Using an OBJECT library syntax-checks and compiles the source files without the overhead of linking.
add_library(${TARGET_PROJECT} OBJECT main.cpp shape.cpp)

# STEP 2: The Test Binary
# Compiles the test executable completely independently from the same source files.
add_executable(${TARGET_PROJECT} main.cpp shape.cpp)
target_link_libraries(${TARGET_PROJECT}_test GTest::gtest_main) # If using GoogleTest

# THE CHAIN: Force Ninja to build Step 1 before Step 2
add_dependencies(${TARGET_PROJECT} ${TARGET_PROJECT}_test)

# (Optional) AUTO-RUN: Execute the test automatically if compilation succeeds
add_custom_command(TARGET ${TARGET_PROJECT}_test POST_BUILD
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_PROJECT}_test
)