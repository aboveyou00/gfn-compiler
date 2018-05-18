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

TEST(SyntaxTreeParser_parse, SimpleLessThan) {
    PARSE_SOURCE("1 < 2"s);

    EXPECT_BIN_OP(expr, "<"s, {
        EXPECT_INTEGER_LITERAL(lhs, 1);
        EXPECT_INTEGER_LITERAL(rhs, 2);
    });
}

TEST(SyntaxTreeParser_parse, SimpleGreaterThan) {
    PARSE_SOURCE("5 > 3"s);

    EXPECT_BIN_OP(expr, ">"s, {
        EXPECT_INTEGER_LITERAL(lhs, 5);
        EXPECT_INTEGER_LITERAL(rhs, 3);
    });
}

TEST(SyntaxTreeParser_parse, SimpleLessThanEquals) {
    PARSE_SOURCE("2 <= 4"s);

    EXPECT_BIN_OP(expr, "<="s, {
        EXPECT_INTEGER_LITERAL(lhs, 2);
        EXPECT_INTEGER_LITERAL(rhs, 4);
    });
}

TEST(SyntaxTreeParser_parse, SimpleGreaterThanEquals) {
    PARSE_SOURCE("15 >= 13"s);

    EXPECT_BIN_OP(expr, ">="s, {
        EXPECT_INTEGER_LITERAL(lhs, 15);
        EXPECT_INTEGER_LITERAL(rhs, 13);
    });
}

TEST(SyntaxTreeParser_parse, OrderOfOperations_Relational_Additive) {
    PARSE_SOURCE("5 < 2 + 3"s);

    EXPECT_BIN_OP(expr, "<"s, {
        EXPECT_INTEGER_LITERAL(lhs, 5);

        EXPECT_BIN_OP(rhs, "+", {
            EXPECT_INTEGER_LITERAL(lhs, 2);
            EXPECT_INTEGER_LITERAL(rhs, 3);
        });
    });
}

TEST(SyntaxTreeParser_parse, OrderOfOperations_Relational_Additive_Override) {
    PARSE_SOURCE("(5 < 2) + 3"s);

    EXPECT_BIN_OP(expr, "+"s, {
        EXPECT_BIN_OP(lhs, "<", {
            EXPECT_INTEGER_LITERAL(lhs, 5);
            EXPECT_INTEGER_LITERAL(rhs, 2);
        });

        EXPECT_INTEGER_LITERAL(rhs, 3);
    });
}

TEST(SyntaxTreeParser_parse, SimpleEquality) {
    PARSE_SOURCE("25 == 41"s);

    EXPECT_BIN_OP(expr, "=="s, {
        EXPECT_INTEGER_LITERAL(lhs, 25);
        EXPECT_INTEGER_LITERAL(rhs, 41);
    });
}

TEST(SyntaxTreeParser_parse, SimpleInequality) {
    PARSE_SOURCE("26 != 43"s);

    EXPECT_BIN_OP(expr, "!="s, {
        EXPECT_INTEGER_LITERAL(lhs, 26);
        EXPECT_INTEGER_LITERAL(rhs, 43);
    });
}

TEST(SyntaxTreeParser_parse, OrderOfOperations_Equality_Relational) {
    PARSE_SOURCE("5 == 2 > 3"s);

    EXPECT_BIN_OP(expr, "=="s, {
        EXPECT_INTEGER_LITERAL(lhs, 5);

        EXPECT_BIN_OP(rhs, ">", {
            EXPECT_INTEGER_LITERAL(lhs, 2);
            EXPECT_INTEGER_LITERAL(rhs, 3);
        });
    });
}

TEST(SyntaxTreeParser_parse, OrderOfOperations_Equality_Relational_Override) {
    PARSE_SOURCE("(5 == 2) > 3"s);

    EXPECT_BIN_OP(expr, ">"s, {
        EXPECT_BIN_OP(lhs, "==", {
            EXPECT_INTEGER_LITERAL(lhs, 5);
            EXPECT_INTEGER_LITERAL(rhs, 2);
        });

        EXPECT_INTEGER_LITERAL(rhs, 3);
    });
}

TEST(SyntaxTreeParser_parse, SimpleConditionalAnd) {
    PARSE_SOURCE("true && false"s);

    EXPECT_BIN_OP(expr, "&&"s, {
        EXPECT_BOOLEAN_LITERAL(lhs, true);
        EXPECT_BOOLEAN_LITERAL(rhs, false);
    });
}

TEST(SyntaxTreeParser_parse, OrderOfOperations_ConditionalAnd_Equality) {
    PARSE_SOURCE("true && false != true"s);

    EXPECT_BIN_OP(expr, "&&"s, {
        EXPECT_BOOLEAN_LITERAL(lhs, true);

        EXPECT_BIN_OP(rhs, "!=", {
            EXPECT_BOOLEAN_LITERAL(lhs, false);
            EXPECT_BOOLEAN_LITERAL(rhs, true);
        });
    });
}

TEST(SyntaxTreeParser_parse, OrderOfOperations_ConditionalAnd_Equality_Override) {
    PARSE_SOURCE("(true && false) != true"s);

    EXPECT_BIN_OP(expr, "!="s, {
        EXPECT_BIN_OP(lhs, "&&", {
            EXPECT_BOOLEAN_LITERAL(lhs, true);
            EXPECT_BOOLEAN_LITERAL(rhs, false);
        });

        EXPECT_BOOLEAN_LITERAL(rhs, true);
    });
}

TEST(SyntaxTreeParser_parse, SimpleConditionalOr) {
    PARSE_SOURCE("false || true"s);

    EXPECT_BIN_OP(expr, "||"s, {
        EXPECT_BOOLEAN_LITERAL(lhs, false);
        EXPECT_BOOLEAN_LITERAL(rhs, true);
    });
}

TEST(SyntaxTreeParser_parse, OrderOfOperations_ConditionalOr_ConditionalAnd) {
    PARSE_SOURCE("false || true && false"s);

    EXPECT_BIN_OP(expr, "||"s, {
        EXPECT_BOOLEAN_LITERAL(lhs, false);

        EXPECT_BIN_OP(rhs, "&&", {
            EXPECT_BOOLEAN_LITERAL(lhs, true);
            EXPECT_BOOLEAN_LITERAL(rhs, false);
        });
    });
}

TEST(SyntaxTreeParser_parse, OrderOfOperations_ConditionalOr_ConditionalAnd_Override) {
    PARSE_SOURCE("(false || true) && true"s);

    EXPECT_BIN_OP(expr, "&&"s, {
        EXPECT_BIN_OP(lhs, "||", {
            EXPECT_BOOLEAN_LITERAL(lhs, false);
            EXPECT_BOOLEAN_LITERAL(rhs, true);
        });

        EXPECT_BOOLEAN_LITERAL(rhs, true);
    });
}
