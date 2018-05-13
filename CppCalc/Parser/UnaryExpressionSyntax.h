#pragma once
#include "Parser/ExpressionSyntax.h"

class UnaryExpressionSyntax :
    public ExpressionSyntax
{
public:
    UnaryExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *expr, const std::string op);
    ~UnaryExpressionSyntax();

    static ExpressionSyntax *tryParse(Cursor<Token*> &cursor);

    ExpressionSyntax *expr() const;
    const std::string op() const;

    virtual void emit(std::vector<Opcode*> &ops) const override;

    virtual void repr(std::stringstream &stream) const;

private:
    ExpressionSyntax *m_expr;
    const std::string m_op;
};
