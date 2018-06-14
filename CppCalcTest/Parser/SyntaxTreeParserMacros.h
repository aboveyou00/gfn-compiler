#pragma once
#include "Tokenizer/Tokenizer.h"
#include "Parser/SyntaxTreeParser.h"
#include "Parser/BinaryExpressionSyntax.h"
#include "Parser/UnaryExpressionSyntax.h"
#include "Parser/PrimaryExpressionSyntax.h"
#include "Parser/ExpressionStatementSyntax.h"
#include "Parser/PrintStatementSyntax.h"
#include "Parser/IfStatementSyntax.h"

#pragma warning (disable: 4456)

#define PARSE_EXPRESSION(str)\
    Tokenizer tokenizer;\
    auto tokens = tokenizer.tokenize(str);\
    SyntaxTreeParser syntaxTreeParser;\
    auto expr = syntaxTreeParser.parseExpression(*tokens);

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

#define PARSE_COMPILATION_UNIT(str)\
    Tokenizer tokenizer;\
    auto tokens = tokenizer.tokenize(str);\
    SyntaxTreeParser syntaxTreeParser;\
    auto block = syntaxTreeParser.parseCompilationUnit(*tokens);\
    auto currentStatementIdx = 0;

#define EXPECT_EXPRESSION_STATEMENT(expr, assertions)\
    {\
        auto __myStmt = dynamic_cast<ExpressionStatementSyntax*>(block->at(currentStatementIdx));\
        EXPECT_TRUE(__myStmt != nullptr);\
        auto expr = __myStmt->expr();\
        {\
            assertions\
        }\
        currentStatementIdx++;\
    }

#define EXPECT_PRINT_STATEMENT(stmtIsPuts, expr, assertions)\
    {\
        auto __myStmt = dynamic_cast<PrintStatementSyntax*>(block->at(currentStatementIdx));\
        EXPECT_TRUE(__myStmt != nullptr);\
        EXPECT_TRUE(__myStmt->isPuts() == stmtIsPuts);\
        auto expr = __myStmt->expr();\
        {\
            assertions\
        }\
        currentStatementIdx++;\
    }

#define EXPECT_IF_STATEMENT(expr, exprAssertions, stmtAssertions)\
    {\
        auto __myStmt = dynamic_cast<IfStatementSyntax*>(block->at(currentStatementIdx));\
        EXPECT_TRUE(__myStmt != nullptr);\
        auto expr = __myStmt->condition();\
        {\
            exprAssertions\
        }\
        auto ifStmt = __myStmt->ifBody();\
        {\
            std::vector<StatementSyntax*> __myBlock { ifStmt };\
            auto block = &__myBlock;\
            auto currentStatementIdx = 0;\
            stmtAssertions\
        }\
        auto elseStmt = __myStmt->elseBody();\
        EXPECT_TRUE(elseStmt == nullptr);\
        currentStatementIdx++;\
    }

#define EXPECT_IF_ELSE_STATEMENT(expr, exprAssertions, ifStmtAssertions, elseStmtAssertions)\
    {\
        auto __myStmt = dynamic_cast<IfStatementSyntax*>(block->at(currentStatementIdx));\
        EXPECT_TRUE(__myStmt != nullptr);\
        auto expr = __myStmt->condition();\
        {\
            exprAssertions\
        }\
        auto ifStmt = __myStmt->ifBody();\
        {\
            std::vector<StatementSyntax*> __myBlock { ifStmt };\
            auto block = &__myBlock;\
            auto currentStatementIdx = 0;\
            ifStmtAssertions\
        }\
        auto elseStmt = __myStmt->elseBody();\
        EXPECT_TRUE(elseStmt != nullptr);\
        {\
            std::vector<StatementSyntax*> __myBlock { elseStmt };\
            auto block = &__myBlock;\
            auto currentStatementIdx = 0;\
            elseStmtAssertions\
        }\
        currentStatementIdx++;\
    }

#define EXPECT_NO_MORE_STATEMENTS()\
    EXPECT_TRUE(block->size() == currentStatementIdx);
