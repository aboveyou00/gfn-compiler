#pragma once
#include "Parser/ExpressionSyntax.h"

class BinaryExpressionSyntax :
    public ExpressionSyntax
{
public:
    BinaryExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *lhs, ExpressionSyntax *rhs, const std::string op);
    ~BinaryExpressionSyntax();

    ExpressionSyntax *lhs() const;
    ExpressionSyntax *rhs() const;
    const std::string op() const;

    virtual void repr(std::stringstream &stream) const;

private:
    ExpressionSyntax *m_lhs;
    ExpressionSyntax *m_rhs;
    const std::string m_op;
};
