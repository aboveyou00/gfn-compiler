#include "stdafx.h"

#include "AdditiveExpressionSyntax.h"

#include "MultiplicativeExpressionSyntax.h"
#include "Token.h"

AdditiveExpressionSyntax::AdditiveExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *lhs, ExpressionSyntax *rhs, const std::string op)
    : BinaryExpressionSyntax(startIndex, length, lhs, rhs, op)
{
}
AdditiveExpressionSyntax::~AdditiveExpressionSyntax()
{
}

ExpressionSyntax *AdditiveExpressionSyntax::tryParse(Cursor<Token*> &cursor)
{
    ExpressionSyntax *expr = tryParseSyntax<MultiplicativeExpressionSyntax>(cursor);
    if (expr == nullptr) return nullptr;

    while (true)
    {
        AdditiveExpressionSyntax *rhsExpr = tryParseRhs(cursor, expr);
        if (rhsExpr == nullptr) return expr;
        else expr = rhsExpr;
    }
}

AdditiveExpressionSyntax *AdditiveExpressionSyntax::tryParseRhs(Cursor<Token*> &cursor, ExpressionSyntax *lhs)
{
    if (!cursor.current()->isOperator()) return nullptr;
    auto op = cursor.current()->op();
    if (op != "+" && op != "-") return nullptr;

    auto snapshot = cursor.snapshot();
    cursor.next();
    ExpressionSyntax *rhs = tryParseSyntax<MultiplicativeExpressionSyntax>(cursor);
    if (rhs == nullptr)
    {
        cursor.reset(snapshot);
        return nullptr;
    }

    auto startIndex = lhs->startIndex();
    return new AdditiveExpressionSyntax(startIndex, cursor.snapshot() - startIndex, lhs, rhs, op);
}
