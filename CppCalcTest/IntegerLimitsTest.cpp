#include "pch.h"
#include "CppCalc.h"

TEST(CppCalc_eval, IntegerLimits_ValidUpperBound) {
    CppCalc calc;
    auto result = calc.eval("2147483647");
    EXPECT_TRUE(result == 2147483647);
}

TEST(CppCalc_eval, IntegerLimits_InvalidUpperBound) {
    CppCalc calc;
    EXPECT_THROW(calc.eval("2147483648"), std::logic_error);
}

TEST(CppCalc_eval, IntegerLimits_WildlyInvalidUpperBound) {
    CppCalc calc;
    EXPECT_THROW(calc.eval("999999999999999999999"), std::logic_error);
}

TEST(CppCalc_eval, IntegerLimits_ValidLowerBound) {
    CppCalc calc;
    auto result = calc.eval("-2147483648");
    EXPECT_TRUE(result == -2147483648);
}

TEST(CppCalc_eval, IntegerLimits_InvalidLowerBound) {
    CppCalc calc;
    EXPECT_THROW(calc.eval("-2147483649"), std::logic_error);
}

TEST(CppCalc_eval, IntegerLimits_WildlyInvalidLowerBound) {
    CppCalc calc;
    EXPECT_THROW(calc.eval("-999999999999999999999"), std::logic_error);
}

TEST(CppCalc_eval, IntegerLimits_InvalidLowerBound_WithSpaceSeparation) {
    CppCalc calc;
    EXPECT_THROW(calc.eval("- 2147483648"), std::logic_error);
}

TEST(CppCalc_eval, IntegerLimits_InvalidLowerBound_Parenthesized) {
    CppCalc calc;
    EXPECT_THROW(calc.eval("-(2147483648)"), std::logic_error);
}

TEST(CppCalc_eval, IntegerLimits_InvalidLowerBound_Additive) {
    CppCalc calc;
    EXPECT_THROW(calc.eval("0-2147483648"), std::logic_error);
}
