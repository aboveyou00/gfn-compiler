#include "pch.h"
#include "GfnCompiler.h"

using namespace Gfn::Compiler;

TEST(GfnCompiler_eval, IntegerLiteral) {
    GfnCompiler calc;
    auto result = calc.eval("25");
    EXPECT_TRUE(result == 25);
}

TEST(GfnCompiler_eval, MaxIntegerLiteral) {
    std::stringstream stream;
    stream << std::numeric_limits<int32_t>::max();

    GfnCompiler calc;
    auto result = calc.eval(stream.str());
    EXPECT_TRUE(result == std::numeric_limits<int32_t>::max());
}

TEST(GfnCompiler_eval, MinIntegerLiteral) {
    std::stringstream stream;
    stream << std::numeric_limits<int32_t>::min();

    GfnCompiler calc;
    auto result = calc.eval(stream.str());
    EXPECT_TRUE(result == std::numeric_limits<int32_t>::min());
}

TEST(GfnCompiler_eval, BooleanLiteral_True) {
    GfnCompiler calc;
    auto result = calc.eval("true");
    EXPECT_TRUE(result == 1);
}

TEST(GfnCompiler_eval, BooleanLiteral_False) {
    GfnCompiler calc;
    auto result = calc.eval("false");
    EXPECT_TRUE(result == 0);
}

TEST(GfnCompiler_eval, SimpleNegation) {
    GfnCompiler calc;
    auto result = calc.eval("-45");
    EXPECT_TRUE(result == -45);
}

TEST(GfnCompiler_eval, UnaryPositive) {
    GfnCompiler calc;
    auto result = calc.eval("+45");
    EXPECT_TRUE(result == 45);
}

TEST(GfnCompiler_eval, LogicalNot_True) {
    GfnCompiler calc;
    auto result = calc.eval("!true");
    EXPECT_TRUE(result == 0);
}

TEST(GfnCompiler_eval, LogicalNot_False) {
    GfnCompiler calc;
    auto result = calc.eval("!false");
    EXPECT_TRUE(result == 1);
}

TEST(GfnCompiler_eval, SimpleAddition) {
    GfnCompiler calc;
    auto result = calc.eval("3 + 4");
    EXPECT_TRUE(result == 7);
}

TEST(GfnCompiler_eval, ComplexAddition) {
    GfnCompiler calc;
    auto result = calc.eval("1 + 2 + 3 + 4 + 5");
    EXPECT_TRUE(result == 15);
}

TEST(GfnCompiler_eval, SimpleSubtraction) {
    GfnCompiler calc;
    auto result = calc.eval("20 - 16");
    EXPECT_TRUE(result == 4);
}

TEST(GfnCompiler_eval, SimpleMultiplication) {
    GfnCompiler calc;
    auto result = calc.eval("5 * 4");
    EXPECT_TRUE(result == 20);
}

TEST(GfnCompiler_eval, SimpleDivision) {
    GfnCompiler calc;
    auto result = calc.eval("360 / 36");
    EXPECT_TRUE(result == 10);
}

TEST(GfnCompiler_eval, SimpleIntegerDivision) {
    GfnCompiler calc;
    auto result = calc.eval("5 / 2");
    EXPECT_TRUE(result == 2);
}

TEST(GfnCompiler_eval, SimpleModulus) {
    GfnCompiler calc;
    auto result = calc.eval("13 % 2");
    EXPECT_TRUE(result == 1);
}

TEST(GfnCompiler_eval, ComplexExpression) {
    GfnCompiler calc;
    auto result = calc.eval("3 + 4 * 5");
    EXPECT_TRUE(result == 23);
}

TEST(GfnCompiler_eval, BooleanEquality_True) {
    GfnCompiler calc;
    auto result = calc.eval("true == true");
    EXPECT_TRUE(result == 1);
}

TEST(GfnCompiler_eval, BooleanEquality_False) {
    GfnCompiler calc;
    auto result = calc.eval("true == false");
    EXPECT_TRUE(result == 0);
}

TEST(GfnCompiler_eval, BooleanInequality) {
    GfnCompiler calc;
    auto result = calc.eval("true != true");
    EXPECT_TRUE(result == 0);
}

TEST(GfnCompiler_eval, Int32Equality_Complex_True) {
    GfnCompiler calc;
    auto result = calc.eval("42 == 21 * 2");
    EXPECT_TRUE(result == 1);
}

TEST(GfnCompiler_eval, Int32LessThan_True) {
    GfnCompiler calc;
    auto result = calc.eval("3 < 5");
    EXPECT_TRUE(result == 1);
}

TEST(GfnCompiler_eval, Int32LessThan_False) {
    GfnCompiler calc;
    auto result = calc.eval("5 < 3");
    EXPECT_TRUE(result == 0);
}

TEST(GfnCompiler_eval, Int32LessThan_Identity) {
    GfnCompiler calc;
    auto result = calc.eval("5 < 5");
    EXPECT_TRUE(result == 0);
}

TEST(GfnCompiler_eval, Int32GreaterThan_True) {
    GfnCompiler calc;
    auto result = calc.eval("5 > 3");
    EXPECT_TRUE(result == 1);
}

TEST(GfnCompiler_eval, Int32GreaterThan_False) {
    GfnCompiler calc;
    auto result = calc.eval("3 > 5");
    EXPECT_TRUE(result == 0);
}

TEST(GfnCompiler_eval, Int32GreaterThan_Identity) {
    GfnCompiler calc;
    auto result = calc.eval("5 > 5");
    EXPECT_TRUE(result == 0);
}

TEST(GfnCompiler_eval, Int32LessThanEquals_True) {
    GfnCompiler calc;
    auto result = calc.eval("3 <= 5");
    EXPECT_TRUE(result == 1);
}

TEST(GfnCompiler_eval, Int32LessThanEquals_False) {
    GfnCompiler calc;
    auto result = calc.eval("5 <= 3");
    EXPECT_TRUE(result == 0);
}

TEST(GfnCompiler_eval, Int32LessThanEquals_Identity) {
    GfnCompiler calc;
    auto result = calc.eval("5 <= 5");
    EXPECT_TRUE(result == 1);
}

TEST(GfnCompiler_eval, Int32GreaterThanEquals_True) {
    GfnCompiler calc;
    auto result = calc.eval("5 >= 3");
    EXPECT_TRUE(result == 1);
}

TEST(GfnCompiler_eval, Int32GreaterThanEquals_False) {
    GfnCompiler calc;
    auto result = calc.eval("3 >= 5");
    EXPECT_TRUE(result == 0);
}

TEST(GfnCompiler_eval, Int32GreaterThanEquals_Identity) {
    GfnCompiler calc;
    auto result = calc.eval("5 >= 5");
    EXPECT_TRUE(result == 1);
}

TEST(GfnCompiler_eval, BooleanInt32Addition) {
    GfnCompiler calc;
    EXPECT_THROW(calc.eval("true + 32"), std::logic_error);
}

TEST(GfnCompiler_eval, Int32BooleanAddition) {
    GfnCompiler calc;
    EXPECT_THROW(calc.eval("32 + true"), std::logic_error);
}

TEST(GfnCompiler_eval, ConditionalAnd_True) {
    GfnCompiler calc;
    auto result = calc.eval("true && true");
    EXPECT_TRUE(result == 1);
}

TEST(GfnCompiler_eval, ConditionalAnd_False) {
    GfnCompiler calc;
    auto result = calc.eval("true && false");
    EXPECT_TRUE(result == 0);
}

TEST(GfnCompiler_eval, ConditionalAnd_False_ShortCircuit) {
    GfnCompiler calc;
    auto result = calc.eval("false && true");
    EXPECT_TRUE(result == 0);
}

TEST(GfnCompiler_eval, ConditionalOr_False) {
    GfnCompiler calc;
    auto result = calc.eval("false || false");
    EXPECT_TRUE(result == 0);
}

TEST(GfnCompiler_eval, ConditionalOr_True) {
    GfnCompiler calc;
    auto result = calc.eval("false || true");
    EXPECT_TRUE(result == 1);
}

TEST(GfnCompiler_eval, ConditionalOr_True_ShortCircuit) {
    GfnCompiler calc;
    auto result = calc.eval("true || false");
    EXPECT_TRUE(result == 1);
}
