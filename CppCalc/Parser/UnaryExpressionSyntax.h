#pragma once
#include "Parser/ExpressionSyntax.h"

class MethodOverload;

class UnaryExpressionSyntax :
    public ExpressionSyntax
{
public:
    static ExpressionSyntax *tryParse(Cursor<Token*> &cursor);

public:
    UnaryExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *expr, const std::string op);
    ~UnaryExpressionSyntax();

    ExpressionSyntax *expr() const;
    const std::string op() const;

    virtual bool tryResolveType() override;

    virtual void emit(std::vector<Opcode*> &ops) const override;

    virtual void repr(std::stringstream &stream) const;

protected:
    virtual std::string getOperatorMethodName() const;

private:
    ExpressionSyntax *m_expr;
    const std::string m_op;

    MethodOverload *m_selectedOperatorOverload;

    bool isNegativeNumericLimit() const;
};
