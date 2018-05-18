#include "stdafx.h"

#include "Parser/EqualityExpressionSyntax.h"

#include "Parser/RelationalExpressionSyntax.h"
#include "Tokenizer/Token.h"

EqualityExpressionSyntax::EqualityExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *lhs, ExpressionSyntax *rhs, const std::string op)
    : BinaryExpressionSyntax(startIndex, length, lhs, rhs, op)
{
}
EqualityExpressionSyntax::~EqualityExpressionSyntax()
{
}

ExpressionSyntax *EqualityExpressionSyntax::tryParse(Cursor<Token*> &cursor)
{
    ExpressionSyntax *expr = tryParseSyntax<RelationalExpressionSyntax>(cursor);
    if (expr == nullptr) return nullptr;

    while (true)
    {
        EqualityExpressionSyntax *rhsExpr = tryParseRhs(cursor, expr);
        if (rhsExpr == nullptr) return expr;
        else expr = rhsExpr;
    }
}

void EqualityExpressionSyntax::emit(std::vector<Opcode*> &ops) const
{
    this->lhs()->emit(ops);
    this->rhs()->emit(ops);

    throw std::logic_error("Not implemented!"s);
}

EqualityExpressionSyntax *EqualityExpressionSyntax::tryParseRhs(Cursor<Token*> &cursor, ExpressionSyntax *lhs)
{
    if (!cursor.current()->isOperator()) return nullptr;
    auto op = cursor.current()->op();
    if (op != "=="s && op != "!="s) return nullptr;

    auto snapshot = cursor.snapshot();
    cursor.next();
    ExpressionSyntax *rhs = tryParseSyntax<RelationalExpressionSyntax>(cursor);
    if (rhs == nullptr)
    {
        cursor.reset(snapshot);
        return nullptr;
    }

    auto startIndex = lhs->startIndex();
    return new EqualityExpressionSyntax(startIndex, cursor.current()->startIndex() - startIndex, lhs, rhs, op);
}
