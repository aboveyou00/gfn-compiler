#pragma once
#include "Parser/BinaryExpressionSyntax.h"

#include <vector>

class MultiplicativeExpressionSyntax :
    public BinaryExpressionSyntax
{
public:
    static ExpressionSyntax *tryParse(Cursor<Token*> &cursor);

private:
    static MultiplicativeExpressionSyntax *tryParseRhs(Cursor<Token*> &cursor, ExpressionSyntax *lhs);

public:
    MultiplicativeExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *lhs, ExpressionSyntax *rhs, const std::string op);
    ~MultiplicativeExpressionSyntax();

protected:
    virtual std::string getOperatorMethodName() const override;
};
