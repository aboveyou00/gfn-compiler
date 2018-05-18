#pragma once
#include "Parser/BinaryExpressionSyntax.h"

#include <vector>

class RelationalExpressionSyntax :
    public BinaryExpressionSyntax
{
public:
    RelationalExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *lhs, ExpressionSyntax *rhs, const std::string op);
    ~RelationalExpressionSyntax();

    static ExpressionSyntax *tryParse(Cursor<Token*> &cursor);

    virtual void emit(std::vector<Opcode*> &ops) const override;

private:
    static RelationalExpressionSyntax *tryParseRhs(Cursor<Token*> &cursor, ExpressionSyntax *lhs);
};
