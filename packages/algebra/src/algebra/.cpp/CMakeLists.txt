# /workspace/packages/algebra/src/algebra/.cpp/
# CMakeLists.txt

set(TARGET_PROJECT "Calculator")
set (MAIN_EXE "MathSolver.cpp")
project(${TARGET_PROJECT})

enable_testing()

# STEP 1: The "Dry" Compile
# Using an OBJECT library syntax-checks and compiles the source files without the overhead of linking.
add_library(${TARGET_PROJECT} STATIC 
    MathLibrary.cpp 
    Calculator.cpp
    BracketParser.cpp
    ExpressionParser.cpp
)
target_include_directories(${TARGET_PROJECT} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# STEP 2: The Compiled Binary
# Compiles the test executable completely independently from the same source files.
add_executable(${TARGET_PROJECT}_test ${MAIN_EXE})
target_link_libraries(
    ${TARGET_PROJECT}_test PRIVATE ${TARGET_PROJECT} GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(${TARGET_PROJECT}_test
    XML_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/reports"
)

# ====================================== #
# Micro-benchmarking macro / build stage #
# ====================================== #
set(AUDIT_SOURCES
    BracketParser.cpp
    InfixToPostfix.cpp
    ExpressionParser.cpp
) # << List the files that needs benchmarking executables.

foreach(source_file IN LISTS AUDIT_SOURCES)

    string(STRIP "${source_file}" clean_source)

    if("${clean_sourc}" STREQUAL "")
        continue()
    endif()

    get_filename_component(file_base ${clean_source} NAME_WE)
    
    set(test_target "${file_base}.benchmark")
    
    add_executable(${test_target} ${clean_source})
    target_link_libraries(${test_target} PRIVATE Calculator TimeIt)
    set_source_files_properties(${clean_source} PROPERTIES COMPILE_DEFINITIONS UNIT_TEST=1)
    add_test(NAME "Benchmark_${filebase}" COMMAND ${test_target})

    # (Optional) Tag it so later benchmarks can be run separately from proper unit tests
    set_tests_properties("Benchmark_${filebase}" PROPERTIES LABELS "Benchmark")

endforeach()