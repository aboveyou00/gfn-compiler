#pragma once
#include "Parser/BinaryExpressionSyntax.h"

#include <vector>

class AdditiveExpressionSyntax :
    public BinaryExpressionSyntax
{
public:
    static ExpressionSyntax *tryParse(Cursor<Token*> &cursor);

private:
    static AdditiveExpressionSyntax *tryParseRhs(Cursor<Token*> &cursor, ExpressionSyntax *lhs);

public:
    AdditiveExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *lhs, ExpressionSyntax *rhs, const std::string op);
    ~AdditiveExpressionSyntax();

protected:
    virtual std::string getOperatorMethodName() const override;
};
