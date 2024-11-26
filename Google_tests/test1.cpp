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

TEST_F(CalculatorTest, HandlesNulls)
{
    std::string expr = "0+0-0+0-0-0+0";
    EXPECT_EQ(0,calculatorDevice.calculate(expr));
}
TEST_F(CalculatorTest, HandlesInput1) {
    std::string expr = "1+2-3+4*2/2+10^2";
    EXPECT_EQ(104,calculatorDevice.calculate(expr));
}
TEST_F(CalculatorTest, HandlesInput2) {
    std::string  expr = "2*2*2^1";
    EXPECT_EQ(8,calculatorDevice.calculate(expr));
}
TEST_F(CalculatorTest, HandlesInput3) {
    std::string expr = "2*4-4^2+81/3^2";
    EXPECT_EQ(1,calculatorDevice.calculate(expr));
}
TEST_F(CalculatorTest, HandlesInput4) {
    std::string expr = "1/1^1*1^100+1-1^100";
    EXPECT_EQ(1,calculatorDevice.calculate(expr));
}
TEST_F(CalculatorTest, HandlesInput5) {
    std::string expr = "1..0";
    EXPECT_EQ(1,calculatorDevice.calculate(expr));
}
TEST_F(CalculatorTest, HandlesInput6) {
    std::string expr = "1.";
    EXPECT_EQ(1,calculatorDevice.calculate(expr));
}
