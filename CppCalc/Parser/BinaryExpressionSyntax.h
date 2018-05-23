#pragma once
#include "Parser/ExpressionSyntax.h"

class MethodOverload;

class BinaryExpressionSyntax :
    public ExpressionSyntax
{
public:
    BinaryExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *lhs, ExpressionSyntax *rhs, const std::string op);
    ~BinaryExpressionSyntax();

    ExpressionSyntax *lhs() const;
    ExpressionSyntax *rhs() const;
    const std::string op() const;

    virtual bool tryResolveType() override;

    virtual void emit(std::vector<Opcode*> &ops) const override;

    virtual void repr(std::stringstream &stream) const;

protected:
    virtual std::string getOperatorMethodName() const = 0;

private:
    ExpressionSyntax *m_lhs;
    ExpressionSyntax *m_rhs;
    const std::string m_op;

    MethodOverload *m_selectedOperatorOverload;
};
