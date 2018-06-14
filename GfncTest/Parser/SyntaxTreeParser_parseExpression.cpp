#include "pch.h"
#include "SyntaxTreeParserMacros.h"

TEST(SyntaxTreeParser_parseExpression, IntegerLiteral) {
    PARSE_EXPRESSION("42"s);

    EXPECT_INTEGER_LITERAL(expr, 42);
}

TEST(SyntaxTreeParser_parseExpression, StringLiteral_Empty) {
    PARSE_EXPRESSION("\"\""s);

    EXPECT_STRING_LITERAL(expr, ""s);
}

TEST(SyntaxTreeParser_parseExpression, StringLiteral_Simple) {
    PARSE_EXPRESSION("\"Hello, World!\""s);

    EXPECT_STRING_LITERAL(expr, "Hello, World!"s);
}

TEST(SyntaxTreeParser_parseExpression, BooleanLiteral) {
    PARSE_EXPRESSION("true"s);

    EXPECT_BOOLEAN_LITERAL(expr, true);
}

TEST(SyntaxTreeParser_parseExpression, ParenthesizedIntegerLiteral) {
    PARSE_EXPRESSION("(285)"s);

    EXPECT_INTEGER_LITERAL(expr, 285);
}

TEST(SyntaxTreeParser_parseExpression, UnaryPositiveLiteral) {
    PARSE_EXPRESSION("+5"s);

    EXPECT_UN_OP(expr, "+"s, {
        EXPECT_INTEGER_LITERAL(expr, 5);
    });
}

TEST(SyntaxTreeParser_parseExpression, UnaryNegativeLiteral) {
    PARSE_EXPRESSION("-16"s);

    EXPECT_UN_OP(expr, "-"s, {
        EXPECT_INTEGER_LITERAL(expr, 16);
    });
}

TEST(SyntaxTreeParser_parseExpression, UnaryLogicalNot) {
    PARSE_EXPRESSION("!true"s);

    EXPECT_UN_OP(expr, "!"s, {
        EXPECT_BOOLEAN_LITERAL(expr, true);
    });
}

TEST(SyntaxTreeParser_parseExpression, MultipleNegations) {
    PARSE_EXPRESSION("---5"s);

    EXPECT_UN_OP(expr, "-"s, {
        EXPECT_UN_OP(expr, "-"s, {
            EXPECT_UN_OP(expr, "-"s, {
                EXPECT_INTEGER_LITERAL(expr, 5);
            });
        });
    });
}

TEST(SyntaxTreeParser_parseExpression, SimpleAddition) {
    PARSE_EXPRESSION("1 + 2"s);

    EXPECT_BIN_OP(expr, "+"s, {
        EXPECT_INTEGER_LITERAL(lhs, 1);
        EXPECT_INTEGER_LITERAL(rhs, 2);
    });
}

TEST(SyntaxTreeParser_parseExpression, ComplexAddition) {
    PARSE_EXPRESSION("1 + 2 + 3"s);

    EXPECT_BIN_OP(expr, "+"s, {
        EXPECT_BIN_OP(lhs, "+", {
            EXPECT_INTEGER_LITERAL(lhs, 1);
            EXPECT_INTEGER_LITERAL(rhs, 2);
        });

        EXPECT_INTEGER_LITERAL(rhs, 3);
    });
}

TEST(SyntaxTreeParser_parseExpression, SimpleSubtraction) {
    PARSE_EXPRESSION("20 - 10"s);

    EXPECT_BIN_OP(expr, "-"s, {
        EXPECT_INTEGER_LITERAL(lhs, 20);
        EXPECT_INTEGER_LITERAL(rhs, 10);
    });
}

TEST(SyntaxTreeParser_parseExpression, SimpleMultiplication) {
    PARSE_EXPRESSION("3 * 4"s);

    EXPECT_BIN_OP(expr, "*"s, {
        EXPECT_INTEGER_LITERAL(lhs, 3);
        EXPECT_INTEGER_LITERAL(rhs, 4);
    });
}

TEST(SyntaxTreeParser_parseExpression, ComplexMultiplication) {
    PARSE_EXPRESSION("1 * 2 * 3"s);

    EXPECT_BIN_OP(expr, "*"s, {
        EXPECT_BIN_OP(lhs, "*", {
            EXPECT_INTEGER_LITERAL(lhs, 1);
            EXPECT_INTEGER_LITERAL(rhs, 2);
        });

        EXPECT_INTEGER_LITERAL(rhs, 3);
    });
}

TEST(SyntaxTreeParser_parseExpression, SimpleDivision) {
    PARSE_EXPRESSION("200 / 25"s);

    EXPECT_BIN_OP(expr, "/"s, {
        EXPECT_INTEGER_LITERAL(lhs, 200);
        EXPECT_INTEGER_LITERAL(rhs, 25);
    });
}

TEST(SyntaxTreeParser_parseExpression, SimpleModulus) {
    PARSE_EXPRESSION("13 % 2"s);

    EXPECT_BIN_OP(expr, "%"s, {
        EXPECT_INTEGER_LITERAL(lhs, 13);
        EXPECT_INTEGER_LITERAL(rhs, 2);
    });
}

TEST(SyntaxTreeParser_parseExpression, OrderOfOperations_Additive_Multiplicative) {
    PARSE_EXPRESSION("5 + 2 * 3"s);

    EXPECT_BIN_OP(expr, "+"s, {
        EXPECT_INTEGER_LITERAL(lhs, 5);

        EXPECT_BIN_OP(rhs, "*", {
            EXPECT_INTEGER_LITERAL(lhs, 2);
            EXPECT_INTEGER_LITERAL(rhs, 3);
        });
    });
}

TEST(SyntaxTreeParser_parseExpression, OrderOfOperations_Additive_Multiplicative_Override) {
    PARSE_EXPRESSION("(5 + 2) * 3"s);

    EXPECT_BIN_OP(expr, "*"s, {
        EXPECT_BIN_OP(lhs, "+", {
            EXPECT_INTEGER_LITERAL(lhs, 5);
            EXPECT_INTEGER_LITERAL(rhs, 2);
        });

        EXPECT_INTEGER_LITERAL(rhs, 3);
    });
}

TEST(SyntaxTreeParser_parseExpression, SimpleLessThan) {
    PARSE_EXPRESSION("1 < 2"s);

    EXPECT_BIN_OP(expr, "<"s, {
        EXPECT_INTEGER_LITERAL(lhs, 1);
        EXPECT_INTEGER_LITERAL(rhs, 2);
    });
}

TEST(SyntaxTreeParser_parseExpression, SimpleGreaterThan) {
    PARSE_EXPRESSION("5 > 3"s);

    EXPECT_BIN_OP(expr, ">"s, {
        EXPECT_INTEGER_LITERAL(lhs, 5);
        EXPECT_INTEGER_LITERAL(rhs, 3);
    });
}

TEST(SyntaxTreeParser_parseExpression, SimpleLessThanEquals) {
    PARSE_EXPRESSION("2 <= 4"s);

    EXPECT_BIN_OP(expr, "<="s, {
        EXPECT_INTEGER_LITERAL(lhs, 2);
        EXPECT_INTEGER_LITERAL(rhs, 4);
    });
}

TEST(SyntaxTreeParser_parseExpression, SimpleGreaterThanEquals) {
    PARSE_EXPRESSION("15 >= 13"s);

    EXPECT_BIN_OP(expr, ">="s, {
        EXPECT_INTEGER_LITERAL(lhs, 15);
        EXPECT_INTEGER_LITERAL(rhs, 13);
    });
}

TEST(SyntaxTreeParser_parseExpression, OrderOfOperations_Relational_Additive) {
    PARSE_EXPRESSION("5 < 2 + 3"s);

    EXPECT_BIN_OP(expr, "<"s, {
        EXPECT_INTEGER_LITERAL(lhs, 5);

        EXPECT_BIN_OP(rhs, "+", {
            EXPECT_INTEGER_LITERAL(lhs, 2);
            EXPECT_INTEGER_LITERAL(rhs, 3);
        });
    });
}

TEST(SyntaxTreeParser_parseExpression, OrderOfOperations_Relational_Additive_Override) {
    PARSE_EXPRESSION("(5 < 2) + 3"s);

    EXPECT_BIN_OP(expr, "+"s, {
        EXPECT_BIN_OP(lhs, "<", {
            EXPECT_INTEGER_LITERAL(lhs, 5);
            EXPECT_INTEGER_LITERAL(rhs, 2);
        });

        EXPECT_INTEGER_LITERAL(rhs, 3);
    });
}

TEST(SyntaxTreeParser_parseExpression, SimpleEquality) {
    PARSE_EXPRESSION("25 == 41"s);

    EXPECT_BIN_OP(expr, "=="s, {
        EXPECT_INTEGER_LITERAL(lhs, 25);
        EXPECT_INTEGER_LITERAL(rhs, 41);
    });
}

TEST(SyntaxTreeParser_parseExpression, SimpleInequality) {
    PARSE_EXPRESSION("26 != 43"s);

    EXPECT_BIN_OP(expr, "!="s, {
        EXPECT_INTEGER_LITERAL(lhs, 26);
        EXPECT_INTEGER_LITERAL(rhs, 43);
    });
}

TEST(SyntaxTreeParser_parseExpression, OrderOfOperations_Equality_Relational) {
    PARSE_EXPRESSION("5 == 2 > 3"s);

    EXPECT_BIN_OP(expr, "=="s, {
        EXPECT_INTEGER_LITERAL(lhs, 5);

        EXPECT_BIN_OP(rhs, ">", {
            EXPECT_INTEGER_LITERAL(lhs, 2);
            EXPECT_INTEGER_LITERAL(rhs, 3);
        });
    });
}

TEST(SyntaxTreeParser_parseExpression, OrderOfOperations_Equality_Relational_Override) {
    PARSE_EXPRESSION("(5 == 2) > 3"s);

    EXPECT_BIN_OP(expr, ">"s, {
        EXPECT_BIN_OP(lhs, "==", {
            EXPECT_INTEGER_LITERAL(lhs, 5);
            EXPECT_INTEGER_LITERAL(rhs, 2);
        });

        EXPECT_INTEGER_LITERAL(rhs, 3);
    });
}

TEST(SyntaxTreeParser_parseExpression, SimpleConditionalAnd) {
    PARSE_EXPRESSION("true && false"s);

    EXPECT_BIN_OP(expr, "&&"s, {
        EXPECT_BOOLEAN_LITERAL(lhs, true);
        EXPECT_BOOLEAN_LITERAL(rhs, false);
    });
}

TEST(SyntaxTreeParser_parseExpression, OrderOfOperations_ConditionalAnd_Equality) {
    PARSE_EXPRESSION("true && false != true"s);

    EXPECT_BIN_OP(expr, "&&"s, {
        EXPECT_BOOLEAN_LITERAL(lhs, true);

        EXPECT_BIN_OP(rhs, "!=", {
            EXPECT_BOOLEAN_LITERAL(lhs, false);
            EXPECT_BOOLEAN_LITERAL(rhs, true);
        });
    });
}

TEST(SyntaxTreeParser_parseExpression, OrderOfOperations_ConditionalAnd_Equality_Override) {
    PARSE_EXPRESSION("(true && false) != true"s);

    EXPECT_BIN_OP(expr, "!="s, {
        EXPECT_BIN_OP(lhs, "&&", {
            EXPECT_BOOLEAN_LITERAL(lhs, true);
            EXPECT_BOOLEAN_LITERAL(rhs, false);
        });

        EXPECT_BOOLEAN_LITERAL(rhs, true);
    });
}

TEST(SyntaxTreeParser_parseExpression, SimpleConditionalOr) {
    PARSE_EXPRESSION("false || true"s);

    EXPECT_BIN_OP(expr, "||"s, {
        EXPECT_BOOLEAN_LITERAL(lhs, false);
        EXPECT_BOOLEAN_LITERAL(rhs, true);
    });
}

TEST(SyntaxTreeParser_parseExpression, OrderOfOperations_ConditionalOr_ConditionalAnd) {
    PARSE_EXPRESSION("false || true && false"s);

    EXPECT_BIN_OP(expr, "||"s, {
        EXPECT_BOOLEAN_LITERAL(lhs, false);

        EXPECT_BIN_OP(rhs, "&&", {
            EXPECT_BOOLEAN_LITERAL(lhs, true);
            EXPECT_BOOLEAN_LITERAL(rhs, false);
        });
    });
}

TEST(SyntaxTreeParser_parseExpression, OrderOfOperations_ConditionalOr_ConditionalAnd_Override) {
    PARSE_EXPRESSION("(false || true) && true"s);

    EXPECT_BIN_OP(expr, "&&"s, {
        EXPECT_BIN_OP(lhs, "||", {
            EXPECT_BOOLEAN_LITERAL(lhs, false);
            EXPECT_BOOLEAN_LITERAL(rhs, true);
        });

        EXPECT_BOOLEAN_LITERAL(rhs, true);
    });
}
