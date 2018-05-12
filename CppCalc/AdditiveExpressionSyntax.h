#pragma once
#include "BinaryExpressionSyntax.h"

class AdditiveExpressionSyntax :
    public BinaryExpressionSyntax
{
public:
    AdditiveExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *lhs, ExpressionSyntax *rhs, const std::string op);
    ~AdditiveExpressionSyntax();

    static ExpressionSyntax *tryParse(Cursor<Token*> &cursor);

private:
    static AdditiveExpressionSyntax *tryParseRhs(Cursor<Token*> &cursor, ExpressionSyntax *lhs);
};
