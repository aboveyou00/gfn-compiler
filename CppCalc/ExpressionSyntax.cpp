#include "stdafx.h"
#include "ExpressionSyntax.h"
#include "AdditiveExpressionSyntax.h"

ExpressionSyntax::ExpressionSyntax(uint32_t startIndex, uint32_t length)
    : Syntax(startIndex, length)
{
}
ExpressionSyntax::~ExpressionSyntax()
{
}

ExpressionSyntax *ExpressionSyntax::tryParse(Cursor<Token*> &cursor)
{
    ExpressionSyntax *expr;

    expr = tryParseSyntax<AdditiveExpressionSyntax>(cursor);
    if (expr != nullptr) return expr;

    return nullptr;
}
