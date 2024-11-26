#include "gtest/gtest.h"
#include "../Calculator.h"
#include <string>
#include <gtest/gtest-spi.h>

class CalculatorTest : public testing::Test {
    protected:

    CalculatorTest() = default;

    Calculator calculatorDevice;

};

TEST_F(CalculatorTest, HandlesJustNumbers) {
    std::string expr;
    for (int i = -10;i<=10;i++) {
        expr = std::to_string(i);
        EXPECT_EQ(i,calculatorDevice.calculate(expr));
    }
}

TEST(TestCalculator, HandlesNulls)
{
    Calculator calculatorDevice;
    std::string expr;
    expr = "0+0-0+0-0-0+0";
    EXPECT_EQ(0,calculatorDevice.calculate(expr));
    expr = "2*4-4^2+81/3^2";
    EXPECT_EQ(1,calculatorDevice.calculate(expr));
    expr = "1/1^1*1^100+1-1^100";
    EXPECT_EQ(1,calculatorDevice.calculate(expr));
    expr = "1..0";
    EXPECT_EQ(1,calculatorDevice.calculate(expr));
    expr = "1.";
    EXPECT_EQ(1,calculatorDevice.calculate(expr));
}
TEST(TestCalculator, HandlesInput1) {
    Calculator calculatorDevice;
    std::string expr = "1+2-3+4*2/2+10^2";
    EXPECT_EQ(104,calculatorDevice.calculate(expr));
}
TEST(TestCalculator, HandlesInput2) {
    Calculator calculatorDevice;
    std::string expr;
    expr = "2*2*2^0";
    EXPECT_EQ(4,calculatorDevice.calculate(expr));
}
