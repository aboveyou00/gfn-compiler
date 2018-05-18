#pragma once
#include "Parser/BinaryExpressionSyntax.h"

#include <vector>

class ConditionalOrExpressionSyntax :
    public BinaryExpressionSyntax
{
public:
    ConditionalOrExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *lhs, ExpressionSyntax *rhs, const std::string op);
    ~ConditionalOrExpressionSyntax();

    static ExpressionSyntax *tryParse(Cursor<Token*> &cursor);

    virtual void emit(std::vector<Opcode*> &ops) const override;

private:
    static ConditionalOrExpressionSyntax *tryParseRhs(Cursor<Token*> &cursor, ExpressionSyntax *lhs);
};
