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
    : Syntax(startIndex, length)
{
}
ExpressionSyntax::~ExpressionSyntax()
{
}
