#include "stdafx.h"

#include "Parser/ConditionalAndExpressionSyntax.h"

#include "Parser/EqualityExpressionSyntax.h"
#include "Tokenizer/Token.h"

ConditionalAndExpressionSyntax::ConditionalAndExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *lhs, ExpressionSyntax *rhs, const std::string op)
    : BinaryExpressionSyntax(startIndex, length, lhs, rhs, op)
{
}
ConditionalAndExpressionSyntax::~ConditionalAndExpressionSyntax()
{
}

ExpressionSyntax *ConditionalAndExpressionSyntax::tryParse(Cursor<Token*> &cursor)
{
    ExpressionSyntax *expr = tryParseSyntax<EqualityExpressionSyntax>(cursor);
    if (expr == nullptr) return nullptr;

    while (true)
    {
        ConditionalAndExpressionSyntax *rhsExpr = tryParseRhs(cursor, expr);
        if (rhsExpr == nullptr) return expr;
        else expr = rhsExpr;
    }
}

void ConditionalAndExpressionSyntax::emit(std::vector<Opcode*> &ops) const
{
    this->lhs()->emit(ops);
    this->rhs()->emit(ops);

    throw std::logic_error("Not implemented!"s);
}

ConditionalAndExpressionSyntax *ConditionalAndExpressionSyntax::tryParseRhs(Cursor<Token*> &cursor, ExpressionSyntax *lhs)
{
    if (!cursor.current()->isOperator()) return nullptr;
    auto op = cursor.current()->op();
    if (op != "&&"s) return nullptr;

    auto snapshot = cursor.snapshot();
    cursor.next();
    ExpressionSyntax *rhs = tryParseSyntax<EqualityExpressionSyntax>(cursor);
    if (rhs == nullptr)
    {
        cursor.reset(snapshot);
        return nullptr;
    }

    auto startIndex = lhs->startIndex();
    return new ConditionalAndExpressionSyntax(startIndex, cursor.current()->startIndex() - startIndex, lhs, rhs, op);
}
