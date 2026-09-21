#include <gtest/gtest.h>

// Test Case idioms: TEST(TestSuiteName, TestName)
TEST(SanityCheck, BasicAssertion) {
    EXPECT_EQ(1 + 1, 2);
}

#include <cstdlib>
#include "Calculator.hpp"


TEST(CalculatorTests, AdditionWorks) 
{
    BaseCalculator C;
    double result = C.calculate(5.0, 3.0, '+');
    std::plus<double> fpadd;
    
    // GoogleTest macro to check if the result equals 8.0
    EXPECT_DOUBLE_EQ(result, fpadd(5.0, 3.0));
}

TEST(CalculatorTests, MultiplicationWorks) 
{
    BaseCalculator C;
    double result = C.calculate(4.0, 2.5, '*');
    std::multiplies<double> fpmul;

    EXPECT_DOUBLE_EQ(result, fpmul(4.0, 2.5));
}

TEST(CalculatorTests, SubstractionWorks)
{
    BaseCalculator C;
    double result = C.calculate(8.2, 1.5, '-');
    std::minus<double> fpminus;

    EXPECT_DOUBLE_EQ(result, fpminus(8.2, 1.5));
}

TEST(CalculatorTests, DivisionWorks)
{
    BaseCalculator C;
    double result = C.calculate(92.4, 8.95, '/');
    std::divides<double> fpdiv;

    EXPECT_DOUBLE_EQ(result, fpdiv(92.4, 8.95));
}