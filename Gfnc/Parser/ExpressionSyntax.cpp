#include "stdafx.h"
#include "Parser/ExpressionSyntax.h"
#include "Parser/ConditionalOrExpressionSyntax.h"

ExpressionSyntax *ExpressionSyntax::tryParse(Cursor<Token*> &cursor)
{
    ExpressionSyntax *expr;

    expr = tryParseSyntax<ConditionalOrExpressionSyntax>(cursor);
    if (expr != nullptr) return expr;

    return nullptr;
}

ExpressionSyntax::ExpressionSyntax(uint32_t startIndex, uint32_t length)
    : Syntax(startIndex, length), m_resolvedType(nullptr)
{
}
ExpressionSyntax::~ExpressionSyntax()
{
}

RuntimeType *ExpressionSyntax::resolvedType()
{
    return this->m_resolvedType;
}

void ExpressionSyntax::assertTypeIsResolved() const
{
    if (this->m_resolvedType == nullptr) throw std::logic_error("This expression's type has not been resolved");
}
