#include "pch.h"
#include "SyntaxTreeParserMacros.h"

TEST(SyntaxTreeParser_parseCompilationUnit, Empty) {
    PARSE_COMPILATION_UNIT(""s);

    EXPECT_NO_MORE_STATEMENTS();
}

TEST(SyntaxTreeParser_parseCompilationUnit, SimpleExpression) {
    PARSE_COMPILATION_UNIT("42;"s);

    EXPECT_EXPRESSION_STATEMENT(expr, {
        EXPECT_INTEGER_LITERAL(expr, 42);
    });

    EXPECT_NO_MORE_STATEMENTS();
}

TEST(SyntaxTreeParser_parseCompilationUnit, SimplePuts) {
    PARSE_COMPILATION_UNIT("puts \"Hello, World!\";"s);

    EXPECT_PRINT_STATEMENT(true, expr, {
        EXPECT_STRING_LITERAL(expr, "Hello, World!"s);
    });

    EXPECT_NO_MORE_STATEMENTS();
}

TEST(SyntaxTreeParser_parseCompilationUnit, SimplePrint) {
    PARSE_COMPILATION_UNIT("print 1234;"s);

    EXPECT_PRINT_STATEMENT(false, expr, {
        EXPECT_INTEGER_LITERAL(expr, 1234);
    });

    EXPECT_NO_MORE_STATEMENTS();
}

TEST(SyntaxTreeParser_parseCompilationUnit, SimpleIf) {
    PARSE_COMPILATION_UNIT("if (true) false;"s);

    EXPECT_IF_STATEMENT(expr, {
        EXPECT_BOOLEAN_LITERAL(expr, true);
    }, {
        EXPECT_EXPRESSION_STATEMENT(expr, {
            EXPECT_BOOLEAN_LITERAL(expr, false);
        });
    });

    EXPECT_NO_MORE_STATEMENTS();
}

TEST(SyntaxTreeParser_parseCompilationUnit, SimpleElse) {
    PARSE_COMPILATION_UNIT("if (true) false; else true;"s);

    EXPECT_IF_ELSE_STATEMENT(expr, {
        EXPECT_BOOLEAN_LITERAL(expr, true);
    }, {
        EXPECT_EXPRESSION_STATEMENT(expr,{
            EXPECT_BOOLEAN_LITERAL(expr, false);
        });
    }, {
        EXPECT_EXPRESSION_STATEMENT(expr,{
            EXPECT_BOOLEAN_LITERAL(expr, true);
        });
    });

    EXPECT_NO_MORE_STATEMENTS();
}
