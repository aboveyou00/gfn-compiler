#include "pch.h"
#include "GfnCompiler.h"

TEST(GfnCompiler_eval, IntegerLimits_ValidUpperBound) {
    GfnCompiler calc;
    auto result = calc.eval("2147483647");
    EXPECT_TRUE(result == 2147483647);
}

TEST(GfnCompiler_eval, IntegerLimits_InvalidUpperBound) {
    GfnCompiler calc;
    EXPECT_THROW(calc.eval("2147483648"), std::logic_error);
}

TEST(GfnCompiler_eval, IntegerLimits_WildlyInvalidUpperBound) {
    GfnCompiler calc;
    EXPECT_THROW(calc.eval("999999999999999999999"), std::logic_error);
}

TEST(GfnCompiler_eval, IntegerLimits_ValidLowerBound) {
    GfnCompiler calc;
    auto result = calc.eval("-2147483648");
    EXPECT_TRUE(result == std::numeric_limits<int32_t>::min());
}

TEST(GfnCompiler_eval, IntegerLimits_InvalidLowerBound) {
    GfnCompiler calc;
    EXPECT_THROW(calc.eval("-2147483649"), std::logic_error);
}

TEST(GfnCompiler_eval, IntegerLimits_WildlyInvalidLowerBound) {
    GfnCompiler calc;
    EXPECT_THROW(calc.eval("-999999999999999999999"), std::logic_error);
}

TEST(GfnCompiler_eval, IntegerLimits_InvalidLowerBound_WithSpaceSeparation) {
    GfnCompiler calc;
    EXPECT_THROW(calc.eval("- 2147483648"), std::logic_error);
}

TEST(GfnCompiler_eval, IntegerLimits_InvalidLowerBound_Parenthesized) {
    GfnCompiler calc;
    EXPECT_THROW(calc.eval("-(2147483648)"), std::logic_error);
}

TEST(GfnCompiler_eval, IntegerLimits_InvalidLowerBound_Additive) {
    GfnCompiler calc;
    EXPECT_THROW(calc.eval("0-2147483648"), std::logic_error);
}
