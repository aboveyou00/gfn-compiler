#include "pch.h"
#include "SyntaxTreeParserMacros.h"

TEST(SyntaxTreeParser_parse, IntegerLiteral) {
    PARSE_SOURCE("42"s);

    EXPECT_INTEGER_LITERAL(expr, 42);
}

TEST(SyntaxTreeParser_parse, BooleanLiteral) {
    PARSE_SOURCE("true"s);

    EXPECT_BOOLEAN_LITERAL(expr, true);
}

TEST(SyntaxTreeParser_parse, ParenthesizedIntegerLiteral) {
    PARSE_SOURCE("(285)"s);

    EXPECT_INTEGER_LITERAL(expr, 285);
}

TEST(SyntaxTreeParser_parse, UnaryPositiveLiteral) {
    PARSE_SOURCE("+5"s);

    EXPECT_UN_OP(expr, "+"s, {
        EXPECT_INTEGER_LITERAL(expr, 5);
    });
}

TEST(SyntaxTreeParser_parse, UnaryNegativeLiteral) {
    PARSE_SOURCE("-16"s);

    EXPECT_UN_OP(expr, "-"s, {
        EXPECT_INTEGER_LITERAL(expr, 16);
    });
}

TEST(SyntaxTreeParser_parse, UnaryLogicalNot) {
    PARSE_SOURCE("!true"s);

    EXPECT_UN_OP(expr, "!"s, {
        EXPECT_BOOLEAN_LITERAL(expr, true);
    });
}

TEST(SyntaxTreeParser_parse, MultipleNegations) {
    PARSE_SOURCE("---5"s);

    EXPECT_UN_OP(expr, "-"s, {
        EXPECT_UN_OP(expr, "-"s, {
            EXPECT_UN_OP(expr, "-"s, {
                EXPECT_INTEGER_LITERAL(expr, 5);
            });
        });
    });
}

TEST(SyntaxTreeParser_parse, SimpleAddition) {
    PARSE_SOURCE("1 + 2"s);

    EXPECT_BIN_OP(expr, "+"s, {
        EXPECT_INTEGER_LITERAL(lhs, 1);
        EXPECT_INTEGER_LITERAL(rhs, 2);
    });
}

TEST(SyntaxTreeParser_parse, ComplexAddition) {
    PARSE_SOURCE("1 + 2 + 3"s);

    EXPECT_BIN_OP(expr, "+"s, {
        EXPECT_BIN_OP(lhs, "+", {
            EXPECT_INTEGER_LITERAL(lhs, 1);
            EXPECT_INTEGER_LITERAL(rhs, 2);
        });

        EXPECT_INTEGER_LITERAL(rhs, 3);
    });
}

TEST(SyntaxTreeParser_parse, SimpleSubtraction) {
    PARSE_SOURCE("20 - 10"s);

    EXPECT_BIN_OP(expr, "-"s, {
        EXPECT_INTEGER_LITERAL(lhs, 20);
        EXPECT_INTEGER_LITERAL(rhs, 10);
    });
}

TEST(SyntaxTreeParser_parse, SimpleMultiplication) {
    PARSE_SOURCE("3 * 4"s);

    EXPECT_BIN_OP(expr, "*"s, {
        EXPECT_INTEGER_LITERAL(lhs, 3);
        EXPECT_INTEGER_LITERAL(rhs, 4);
    });
}

TEST(SyntaxTreeParser_parse, ComplexMultiplication) {
    PARSE_SOURCE("1 * 2 * 3"s);

    EXPECT_BIN_OP(expr, "*"s, {
        EXPECT_BIN_OP(lhs, "*", {
            EXPECT_INTEGER_LITERAL(lhs, 1);
            EXPECT_INTEGER_LITERAL(rhs, 2);
        });

        EXPECT_INTEGER_LITERAL(rhs, 3);
    });
}

TEST(SyntaxTreeParser_parse, SimpleDivision) {
    PARSE_SOURCE("200 / 25"s);

    EXPECT_BIN_OP(expr, "/"s, {
        EXPECT_INTEGER_LITERAL(lhs, 200);
        EXPECT_INTEGER_LITERAL(rhs, 25);
    });
}

TEST(SyntaxTreeParser_parse, SimpleModulus) {
    PARSE_SOURCE("13 % 2"s);

    EXPECT_BIN_OP(expr, "%"s, {
        EXPECT_INTEGER_LITERAL(lhs, 13);
        EXPECT_INTEGER_LITERAL(rhs, 2);
    });
}

TEST(SyntaxTreeParser_parse, OrderOfOperations_Additive_Multiplicative) {
    PARSE_SOURCE("5 + 2 * 3"s);

    EXPECT_BIN_OP(expr, "+"s, {
        EXPECT_INTEGER_LITERAL(lhs, 5);

        EXPECT_BIN_OP(rhs, "*", {
            EXPECT_INTEGER_LITERAL(lhs, 2);
            EXPECT_INTEGER_LITERAL(rhs, 3);
        });
    });
}

TEST(SyntaxTreeParser_parse, OrderOfOperations_Additive_Multiplicative_Override) {
    PARSE_SOURCE("(5 + 2) * 3"s);

    EXPECT_BIN_OP(expr, "*"s, {
        EXPECT_BIN_OP(lhs, "+", {
            EXPECT_INTEGER_LITERAL(lhs, 5);
            EXPECT_INTEGER_LITERAL(rhs, 2);
        });

        EXPECT_INTEGER_LITERAL(rhs, 3);
    });
}
