#include "stdafx.h"

#include "Parser/ConditionalOrExpressionSyntax.h"

#include "Parser/ConditionalAndExpressionSyntax.h"
#include "Tokenizer/Token.h"
#include "Runtime/RuntimeType.h"

ExpressionSyntax *ConditionalOrExpressionSyntax::tryParse(Cursor<Token*> &cursor)
{
    ExpressionSyntax *expr = tryParseSyntax<ConditionalAndExpressionSyntax>(cursor);
    if (expr == nullptr) return nullptr;

    while (true)
    {
        ConditionalOrExpressionSyntax *rhsExpr = tryParseRhs(cursor, expr);
        if (rhsExpr == nullptr) return expr;
        else expr = rhsExpr;
    }
}

ConditionalOrExpressionSyntax *ConditionalOrExpressionSyntax::tryParseRhs(Cursor<Token*> &cursor, ExpressionSyntax *lhs)
{
    if (!cursor.current()->isOperator()) return nullptr;
    auto op = cursor.current()->op();
    if (op != "||"s) return nullptr;

    auto snapshot = cursor.snapshot();
    cursor.next();
    ExpressionSyntax *rhs = tryParseSyntax<ConditionalAndExpressionSyntax>(cursor);
    if (rhs == nullptr)
    {
        cursor.reset(snapshot);
        return nullptr;
    }

    auto startIndex = lhs->startIndex();
    return new ConditionalOrExpressionSyntax(startIndex, cursor.current()->startIndex() - startIndex, lhs, rhs, op);
}

ConditionalOrExpressionSyntax::ConditionalOrExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *lhs, ExpressionSyntax *rhs, const std::string op)
    : BinaryExpressionSyntax(startIndex, length, lhs, rhs, op)
{
}
ConditionalOrExpressionSyntax::~ConditionalOrExpressionSyntax()
{
}

bool ConditionalOrExpressionSyntax::tryResolveType()
{
    if (this->m_resolvedType != nullptr) return true;

    if (!this->lhs()->tryResolveType()) return false;
    if (!this->rhs()->tryResolveType()) return false;

    auto leftType = this->lhs()->resolvedType();
    auto rightType = this->rhs()->resolvedType();

    if (leftType != RuntimeType::boolean() || rightType != RuntimeType::boolean()) return false;

    this->m_resolvedType = RuntimeType::boolean();
    return true;
}

void ConditionalOrExpressionSyntax::emit(std::vector<Opcode*> &ops) const
{
    this->lhs()->emit(ops);
    this->rhs()->emit(ops);

    throw std::logic_error("Not implemented!"s);
}

std::string ConditionalOrExpressionSyntax::getOperatorMethodName() const
{
    throw std::logic_error("Conditional \"or\" expressions do not have overloadable operator method names."s);
}
