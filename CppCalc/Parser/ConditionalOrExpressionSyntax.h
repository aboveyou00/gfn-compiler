#pragma once
#include "Parser/BinaryExpressionSyntax.h"

#include <vector>

class ConditionalOrExpressionSyntax :
    public BinaryExpressionSyntax
{
public:
    static ExpressionSyntax *tryParse(Cursor<Token*> &cursor);

private:
    static ConditionalOrExpressionSyntax *tryParseRhs(Cursor<Token*> &cursor, ExpressionSyntax *lhs);

public:
    ConditionalOrExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *lhs, ExpressionSyntax *rhs, const std::string op);
    ~ConditionalOrExpressionSyntax();

    virtual void emit(std::vector<Opcode*> &ops) const override;

protected:
    virtual std::string getOperatorMethodName() const override;
};
