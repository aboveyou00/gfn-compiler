#include "stdafx.h"

#include "MultiplicativeExpressionSyntax.h"

#include "UnaryExpressionSyntax.h"
#include "Token.h"

MultiplicativeExpressionSyntax::MultiplicativeExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *lhs, ExpressionSyntax *rhs, const std::string op)
    : BinaryExpressionSyntax(startIndex, length, lhs, rhs, op)
{
}
MultiplicativeExpressionSyntax::~MultiplicativeExpressionSyntax()
{
}

ExpressionSyntax *MultiplicativeExpressionSyntax::tryParse(Cursor<Token*> &cursor)
{
    ExpressionSyntax *expr = tryParseSyntax<UnaryExpressionSyntax>(cursor);
    if (expr == nullptr) return nullptr;

    while (true)
    {
        MultiplicativeExpressionSyntax *rhsExpr = tryParseRhs(cursor, expr);
        if (rhsExpr == nullptr) return expr;
        else expr = rhsExpr;
    }
}

MultiplicativeExpressionSyntax *MultiplicativeExpressionSyntax::tryParseRhs(Cursor<Token*> &cursor, ExpressionSyntax *lhs)
{
    if (!cursor.current()->isOperator()) return nullptr;
    auto op = cursor.current()->op();
    if (op != "*" && op != "/" && op != "%") return nullptr;

    auto snapshot = cursor.snapshot();
    cursor.next();
    ExpressionSyntax *rhs = tryParseSyntax<UnaryExpressionSyntax>(cursor);
    if (rhs == nullptr)
    {
        cursor.reset(snapshot);
        return nullptr;
    }

    auto startIndex = lhs->startIndex();
    return new MultiplicativeExpressionSyntax(startIndex, cursor.snapshot() - startIndex, lhs, rhs, op);
}
