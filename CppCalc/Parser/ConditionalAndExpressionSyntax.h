#pragma once
#include "Parser/BinaryExpressionSyntax.h"

#include <vector>

class ConditionalAndExpressionSyntax :
    public BinaryExpressionSyntax
{
public:
    ConditionalAndExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *lhs, ExpressionSyntax *rhs, const std::string op);
    ~ConditionalAndExpressionSyntax();

    static ExpressionSyntax *tryParse(Cursor<Token*> &cursor);

    virtual void emit(std::vector<Opcode*> &ops) const override;

private:
    static ConditionalAndExpressionSyntax *tryParseRhs(Cursor<Token*> &cursor, ExpressionSyntax *lhs);
};
