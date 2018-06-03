#pragma once
#include "Tokenizer/Tokenizer.h"
#include "Parser/SyntaxTreeParser.h"
#include "Parser/BinaryExpressionSyntax.h"
#include "Parser/UnaryExpressionSyntax.h"
#include "Parser/PrimaryExpressionSyntax.h"

#pragma warning (disable: 4456)

#define PARSE_SOURCE(str)\
    Tokenizer tokenizer;\
    auto tokens = tokenizer.tokenize(str);\
    SyntaxTreeParser syntaxTreeParser;\
    auto expr = syntaxTreeParser.parseExpression(*tokens);\

#define EXPECT_NULL(expr)\
    EXPECT_TRUE(expr == nullptr);

#define EXPECT_BIN_OP(expr, expectedOp, assertions)\
    {\
        auto __myExpr = dynamic_cast<BinaryExpressionSyntax*>(expr);\
        EXPECT_TRUE(__myExpr != nullptr);\
        EXPECT_TRUE(__myExpr->op() == expectedOp);\
        auto lhs = __myExpr->lhs();\
        auto rhs = __myExpr->rhs();\
        {\
            assertions\
        }\
    }

#define EXPECT_UN_OP(expr, expectedOp, assertions)\
    {\
        auto __myExpr = dynamic_cast<UnaryExpressionSyntax*>(expr);\
        EXPECT_TRUE(__myExpr != nullptr);\
        EXPECT_TRUE(__myExpr->op() == expectedOp);\
        auto expr = __myExpr->expr();\
        {\
            assertions\
        }\
    }

#define EXPECT_INTEGER_LITERAL(expr, val)\
    {\
        auto __myExpr = dynamic_cast<PrimaryExpressionSyntax*>(expr);\
        EXPECT_TRUE(__myExpr != nullptr);\
        EXPECT_TRUE(__myExpr->type() == PrimaryExpressionType::IntegerLiteral);\
        EXPECT_TRUE(__myExpr->intLiteralValue() == val);\
    }

#define EXPECT_ANY_INTEGER_LITERAL(expr)\
    {\
        auto __myExpr = dynamic_cast<PrimaryExpressionSyntax*>(expr);\
        EXPECT_TRUE(__myExpr != nullptr);\
        EXPECT_TRUE(__myExpr->type() == PrimaryExpressionType::IntegerLiteral);\
    }

#define EXPECT_STRING_LITERAL(expr, val)\
    {\
        auto __myExpr = dynamic_cast<PrimaryExpressionSyntax*>(expr);\
        EXPECT_TRUE(__myExpr != nullptr);\
        EXPECT_TRUE(__myExpr->type() == PrimaryExpressionType::StringLiteral);\
        EXPECT_TRUE(__myExpr->stringLiteralValue() == val);\
    }

#define EXPECT_ANY_STRING_LITERAL(expr)\
    {\
        auto __myExpr = dynamic_cast<PrimaryExpressionSyntax*>(expr);\
        EXPECT_TRUE(__myExpr != nullptr);\
        EXPECT_TRUE(__myExpr->type() == PrimaryExpressionType::StringLiteral);\
    }

#define EXPECT_BOOLEAN_LITERAL(expr, val)\
    {\
        auto __myExpr = dynamic_cast<PrimaryExpressionSyntax*>(expr);\
        EXPECT_TRUE(__myExpr != nullptr);\
        EXPECT_TRUE(__myExpr->type() == PrimaryExpressionType::BooleanLiteral);\
        EXPECT_TRUE(__myExpr->booleanLiteralValue() == val);\
    }

#define EXPECT_ANY_BOOLEAN_LITERAL(expr)\
    {\
        auto __myExpr = dynamic_cast<PrimaryExpressionSyntax*>(expr);\
        EXPECT_TRUE(__myExpr != nullptr);\
        EXPECT_TRUE(__myExpr->type() == PrimaryExpressionType::BooleanLiteral);\
    }
