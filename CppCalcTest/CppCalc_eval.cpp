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

TEST(CppCalc_eval, BooleanLiteral_True) {
    CppCalc calc;
    auto result = calc.eval("true");
    EXPECT_TRUE(result == 1);
}

TEST(CppCalc_eval, BooleanLiteral_False) {
    CppCalc calc;
    auto result = calc.eval("false");
    EXPECT_TRUE(result == 0);
}

TEST(CppCalc_eval, SimpleNegation) {
    CppCalc calc;
    auto result = calc.eval("-45");
    EXPECT_TRUE(result == -45);
}

TEST(CppCalc_eval, UnaryPositive) {
    CppCalc calc;
    auto result = calc.eval("+45");
    EXPECT_TRUE(result == 45);
}

TEST(CppCalc_eval, LogicalNot_True) {
    CppCalc calc;
    auto result = calc.eval("!true");
    EXPECT_TRUE(result == 0);
}

TEST(CppCalc_eval, LogicalNot_False) {
    CppCalc calc;
    auto result = calc.eval("!false");
    EXPECT_TRUE(result == 1);
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

TEST(CppCalc_eval, BooleanEquality_True) {
    CppCalc calc;
    auto result = calc.eval("true == true");
    EXPECT_TRUE(result == 1);
}

TEST(CppCalc_eval, BooleanEquality_False) {
    CppCalc calc;
    auto result = calc.eval("true == false");
    EXPECT_TRUE(result == 0);
}

TEST(CppCalc_eval, BooleanInequality) {
    CppCalc calc;
    auto result = calc.eval("true != true");
    EXPECT_TRUE(result == 0);
}

TEST(CppCalc_eval, Int32Equality_Complex_True) {
    CppCalc calc;
    auto result = calc.eval("42 == 21 * 2");
    EXPECT_TRUE(result == 1);
}

TEST(CppCalc_eval, Int32LessThan_True) {
    CppCalc calc;
    auto result = calc.eval("3 < 5");
    EXPECT_TRUE(result == 1);
}

TEST(CppCalc_eval, Int32LessThan_False) {
    CppCalc calc;
    auto result = calc.eval("5 < 3");
    EXPECT_TRUE(result == 0);
}

TEST(CppCalc_eval, Int32LessThan_Identity) {
    CppCalc calc;
    auto result = calc.eval("5 < 5");
    EXPECT_TRUE(result == 0);
}

TEST(CppCalc_eval, Int32GreaterThan_True) {
    CppCalc calc;
    auto result = calc.eval("5 > 3");
    EXPECT_TRUE(result == 1);
}

TEST(CppCalc_eval, Int32GreaterThan_False) {
    CppCalc calc;
    auto result = calc.eval("3 > 5");
    EXPECT_TRUE(result == 0);
}

TEST(CppCalc_eval, Int32GreaterThan_Identity) {
    CppCalc calc;
    auto result = calc.eval("5 > 5");
    EXPECT_TRUE(result == 0);
}

TEST(CppCalc_eval, Int32LessThanEquals_True) {
    CppCalc calc;
    auto result = calc.eval("3 <= 5");
    EXPECT_TRUE(result == 1);
}

TEST(CppCalc_eval, Int32LessThanEquals_False) {
    CppCalc calc;
    auto result = calc.eval("5 <= 3");
    EXPECT_TRUE(result == 0);
}

TEST(CppCalc_eval, Int32LessThanEquals_Identity) {
    CppCalc calc;
    auto result = calc.eval("5 <= 5");
    EXPECT_TRUE(result == 1);
}

TEST(CppCalc_eval, Int32GreaterThanEquals_True) {
    CppCalc calc;
    auto result = calc.eval("5 >= 3");
    EXPECT_TRUE(result == 1);
}

TEST(CppCalc_eval, Int32GreaterThanEquals_False) {
    CppCalc calc;
    auto result = calc.eval("3 >= 5");
    EXPECT_TRUE(result == 0);
}

TEST(CppCalc_eval, Int32GreaterThanEquals_Identity) {
    CppCalc calc;
    auto result = calc.eval("5 >= 5");
    EXPECT_TRUE(result == 1);
}

TEST(CppCalc_eval, BooleanInt32Addition) {
    CppCalc calc;
    EXPECT_THROW(calc.eval("true + 32"), std::logic_error);
}

TEST(CppCalc_eval, Int32BooleanAddition) {
    CppCalc calc;
    EXPECT_THROW(calc.eval("32 + true"), std::logic_error);
}

TEST(CppCalc_eval, ConditionalAnd_True) {
    CppCalc calc;
    auto result = calc.eval("true && true");
    EXPECT_TRUE(result == 1);
}

TEST(CppCalc_eval, ConditionalAnd_False) {
    CppCalc calc;
    auto result = calc.eval("true && false");
    EXPECT_TRUE(result == 0);
}

TEST(CppCalc_eval, ConditionalAnd_False_ShortCircuit) {
    CppCalc calc;
    auto result = calc.eval("false && true");
    EXPECT_TRUE(result == 0);
}

TEST(CppCalc_eval, ConditionalOr_False) {
    CppCalc calc;
    auto result = calc.eval("false || false");
    EXPECT_TRUE(result == 0);
}

TEST(CppCalc_eval, ConditionalOr_True) {
    CppCalc calc;
    auto result = calc.eval("false || true");
    EXPECT_TRUE(result == 1);
}

TEST(CppCalc_eval, ConditionalOr_True_ShortCircuit) {
    CppCalc calc;
    auto result = calc.eval("true || false");
    EXPECT_TRUE(result == 1);
}
