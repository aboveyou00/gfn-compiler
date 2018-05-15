#include "pch.h"
#include "CppCalc.h"

TEST(CppCalc_eval, IntegerLiteral) {
    CppCalc calc;
    auto result = calc.eval("25");
    EXPECT_TRUE(result == 25);
}

TEST(CppCalc_eval, MaxIntegerLiteral) {
    std::stringstream stream;
    stream << std::numeric_limits<int32_t>::max();

    CppCalc calc;
    auto result = calc.eval(stream.str());
    EXPECT_TRUE(result == std::numeric_limits<int32_t>::max());
}

TEST(CppCalc_eval, MinIntegerLiteral) {
    std::stringstream stream;
    stream << std::numeric_limits<int32_t>::min();

    CppCalc calc;
    auto result = calc.eval(stream.str());
    EXPECT_TRUE(result == std::numeric_limits<int32_t>::min());
}

TEST(CppCalc_eval, SimpleNegation) {
    CppCalc calc;
    auto result = calc.eval("-45");
    EXPECT_TRUE(result == -45);
}

TEST(CppCalc_eval, SimpleAddition) {
    CppCalc calc;
    auto result = calc.eval("3 + 4");
    EXPECT_TRUE(result == 7);
}

TEST(CppCalc_eval, ComplexAddition) {
    CppCalc calc;
    auto result = calc.eval("1 + 2 + 3 + 4 + 5");
    EXPECT_TRUE(result == 15);
}

TEST(CppCalc_eval, SimpleSubtraction) {
    CppCalc calc;
    auto result = calc.eval("20 - 16");
    EXPECT_TRUE(result == 4);
}

TEST(CppCalc_eval, SimpleMultiplication) {
    CppCalc calc;
    auto result = calc.eval("5 * 4");
    EXPECT_TRUE(result == 20);
}

TEST(CppCalc_eval, SimpleDivision) {
    CppCalc calc;
    auto result = calc.eval("360 / 36");
    EXPECT_TRUE(result == 10);
}

TEST(CppCalc_eval, SimpleIntegerDivision) {
    CppCalc calc;
    auto result = calc.eval("5 / 2");
    EXPECT_TRUE(result == 2);
}

TEST(CppCalc_eval, SimpleModulus) {
    CppCalc calc;
    auto result = calc.eval("13 % 2");
    EXPECT_TRUE(result == 1);
}

TEST(CppCalc_eval, ComplexExpression) {
    CppCalc calc;
    auto result = calc.eval("3 + 4 * 5");
    EXPECT_TRUE(result == 23);
}
