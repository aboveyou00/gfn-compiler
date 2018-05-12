#pragma once
#include "BinaryExpressionSyntax.h"

class MultiplicativeExpressionSyntax :
    public BinaryExpressionSyntax
{
public:
    MultiplicativeExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *lhs, ExpressionSyntax *rhs, const std::string op);
    ~MultiplicativeExpressionSyntax();

    static ExpressionSyntax *tryParse(Cursor<Token*> &cursor);

private:
    static MultiplicativeExpressionSyntax *tryParseRhs(Cursor<Token*> &cursor, ExpressionSyntax *lhs);
};
