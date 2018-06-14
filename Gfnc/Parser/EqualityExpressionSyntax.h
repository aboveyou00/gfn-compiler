#pragma once
#include "Parser/BinaryExpressionSyntax.h"

#include <vector>

class EqualityExpressionSyntax :
    public BinaryExpressionSyntax
{
public:
    static ExpressionSyntax *tryParse(Cursor<Token*> &cursor);

private:
    static EqualityExpressionSyntax *tryParseRhs(Cursor<Token*> &cursor, ExpressionSyntax *lhs);

public:
    EqualityExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *lhs, ExpressionSyntax *rhs, const std::string op);
    ~EqualityExpressionSyntax();

protected:
    virtual std::string getOperatorMethodName() const override;
};
