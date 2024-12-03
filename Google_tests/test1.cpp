#include "gtest/gtest.h"
#include "../Calculator.h"
#include <string>
#include <gtest/gtest-spi.h>

class CalculatorTest : public testing::Test {
    protected:

    CalculatorTest() = default;

    Calculator calculatorDevice;

};
class StackTesting : public ::testing::Test {
protected:
    StackTesting() = default;
    Stack<long double> stack;
    Stack<long double> stack2;
};
TEST_F(StackTesting, test1) {
    stack<<(15);
    ASSERT_EQ(stack.top(), 15);
}
TEST_F(StackTesting, test2) {
    stack<<(15);
    stack<<(17);
    stack<<(21);
    EXPECT_EQ(stack.top(), 21);
}
TEST_F(StackTesting, test3) {
    EXPECT_THROW(stack.pop(),std::out_of_range);
}
TEST_F(StackTesting, test4) {
    long double t;
    EXPECT_THROW(stack>>(t),std::out_of_range);
}
TEST_F(StackTesting, test5) {
    ASSERT_EQ(stack.empty(), true);
}
TEST_F(StackTesting, test6) {
    stack<<(15);
    ASSERT_EQ(stack.empty(), false);
}
TEST_F(StackTesting, test7) {
    ASSERT_EQ(stack==stack2, true);
}
TEST_F(StackTesting, test8) {
    EXPECT_THROW(stack.top(),std::out_of_range);
}
TEST_F(StackTesting, test9) {
    stack<<(15);
    stack2<<(17);
    EXPECT_EQ(stack>stack2, false);
}
TEST_F(StackTesting, test10) {
    stack<<(17);
    stack2<<(15);
    EXPECT_EQ(stack>stack2, true);
}
TEST_F(StackTesting, test11) {
    stack<<(15);
    stack<<(17);
    stack<<(42);
    EXPECT_EQ(stack>stack2, true);
}
TEST_F(StackTesting, test12) {
    stack<<(15);
    stack<<(17);
    stack<<(42);
    EXPECT_EQ(stack2<stack, true);
}
TEST_F(StackTesting, test13) {
    stack<<(15);
    stack<<(17);
    stack<<(42);
    EXPECT_EQ(stack2>stack, false);
}
TEST_F(StackTesting, test14) {
    stack<<(15);
    stack<<(17);
    stack<<(42);
    stack2 = stack;
    EXPECT_EQ(stack2==stack, true);
}
TEST_F(StackTesting, test15) {
    stack<<(15);
    stack<<(17);
    stack<<(42);
    stack2 = stack;
    EXPECT_EQ(stack2!=stack, false);
}
TEST_F(StackTesting, test16) {
    EXPECT_THROW(stack[0231-57],std::out_of_range);
}
TEST_F(StackTesting, test17) {
    stack<<(15);
    EXPECT_EQ(stack[0],15);
}
TEST_F(StackTesting, test18) {
    ASSERT_EQ(stack.size(), 0);
}
TEST_F(StackTesting, test19) {
    stack<<(15);
    ASSERT_EQ(stack.size(), 1);
}
TEST_F(StackTesting, test20) {
    ASSERT_EQ(stack.capacity(), 16);
}

TEST_F(CalculatorTest, HandlesJustNumbers) {
    std::string expr;
    for (int i = -10;i<=10;i++) {
        expr = std::to_string(i);
        EXPECT_EQ(i,calculatorDevice.processString(expr));
    }
}

TEST_F(CalculatorTest, HandlesNulls)
{
    std::string expr = "0+0-0+0-0-0+0";
    EXPECT_EQ(0,calculatorDevice.processString(expr));
}
TEST_F(CalculatorTest, HandlesInput1) {
    std::string expr = "1+2-3+4*2/2+10^2";
    EXPECT_EQ(104,calculatorDevice.processString(expr));
}
TEST_F(CalculatorTest, HandlesInput2) {
    std::string  expr = "2*2*2^1";
    EXPECT_EQ(8,calculatorDevice.processString(expr));
}
TEST_F(CalculatorTest, HandlesInput3) {
    std::string expr = "2*4-4^2+81/3^2";
    EXPECT_EQ(1,calculatorDevice.processString(expr));
}
TEST_F(CalculatorTest, HandlesInput4) {
    std::string expr = "1/1^1*1^100+1-1^100";
    EXPECT_EQ(1,calculatorDevice.processString(expr));
}
TEST_F(CalculatorTest, HandlesInput5) {
    std::string expr = "1..0";
    EXPECT_EQ(1,calculatorDevice.processString(expr));
}
TEST_F(CalculatorTest, HandlesInput6) {
    std::string expr = "1.";
    EXPECT_EQ(1,calculatorDevice.processString(expr));
}
TEST_F(CalculatorTest, HandlesInput7) {
    std::string expr = "sqrt9";
    EXPECT_EQ(3,calculatorDevice.processString(expr));
}
TEST_F(CalculatorTest, HandlesInput8) {
    std::string expr = "sqrt0";
    EXPECT_EQ(0,calculatorDevice.processString(expr));
}
TEST_F(CalculatorTest, HandlesInput9) {
    std::string expr = "sqrt81";
    EXPECT_EQ(9,calculatorDevice.processString(expr));
}
TEST_F(CalculatorTest, HandlesInput10) {
    std::string expr = "sqrt9*sin0";
    EXPECT_EQ(0,calculatorDevice.processString(expr));
}
TEST_F(CalculatorTest, HandlesInput11) {
    std::string expr = "1+sqrt(18/2*2/3*3/2)+sin(0)";
    EXPECT_EQ(4,calculatorDevice.processString(expr));
}
TEST_F(CalculatorTest, HandlesInput12) {
    std::string expr = "(0+2^2-4*sqrt(1))^2";
    EXPECT_EQ(0,calculatorDevice.processString(expr));
}
TEST_F(CalculatorTest, HandlesInput13) {
    std::string expr = "-15+20*(-1)^3";
    EXPECT_EQ(-35,calculatorDevice.processString(expr));
}
TEST_F(CalculatorTest, HandlesInput14) {
    std::string expr = "1=";
    EXPECT_THROW(calculatorDevice.processString(expr),std::invalid_argument);
}
TEST_F(CalculatorTest, HandlesInput15) {
    std::string expr = "1=124972301746-930-7//ds'v,;dsmvpn123956==43--951028";
    EXPECT_THROW(calculatorDevice.processString(expr),std::invalid_argument);
}
TEST_F(CalculatorTest, HandlesInput16) {
    std::string expr = "(1+2*(-2/(-1)))";
    EXPECT_EQ(5,calculatorDevice.processString(expr));
}
TEST_F(CalculatorTest, HandlesInput17) {
    std::string expr = "sqrt(9)*(1+2-(sqrt(169)*sin(0)))";
    EXPECT_EQ(9,calculatorDevice.processString(expr));
}
TEST_F(CalculatorTest, HandlesInput18) {
    std::string expr = "3/3*(3*3)*3/3+3";
    EXPECT_EQ(12,calculatorDevice.processString(expr));
}
TEST_F(CalculatorTest, HandlesInput19) {
    std::string expr = "-(-(-(-(-1))))";
    EXPECT_EQ(-1,calculatorDevice.processString(expr));
}
TEST_F(CalculatorTest, HandlesInput20) {
    std::string expr = "2^(1+3^(2))";
    EXPECT_EQ(1024,calculatorDevice.processString(expr));
}
TEST_F(CalculatorTest, HandlesInput21) {
    std::string expr = "aaaaaahelphelphelp";
    EXPECT_THROW(calculatorDevice.processString(expr),std::invalid_argument);
}