#include "stdafx.h"

#include "Parser/ConditionalAndExpressionSyntax.h"

#include "Parser/EqualityExpressionSyntax.h"
#include "Tokenizer/Token.h"
#include "Runtime/RuntimeType.h"

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

ConditionalAndExpressionSyntax::ConditionalAndExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *lhs, ExpressionSyntax *rhs, const std::string op)
    : BinaryExpressionSyntax(startIndex, length, lhs, rhs, op)
{
}
ConditionalAndExpressionSyntax::~ConditionalAndExpressionSyntax()
{
}

bool ConditionalAndExpressionSyntax::tryResolveType()
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

void ConditionalAndExpressionSyntax::emit(std::vector<Opcode*> &ops) const
{
    this->lhs()->emit(ops);
    this->rhs()->emit(ops);

    throw std::logic_error("Not implemented!"s);
}

std::string ConditionalAndExpressionSyntax::getOperatorMethodName() const
{
    throw std::logic_error("Conditional \"and\" expressions do not have overloadable operator method names."s);
}
