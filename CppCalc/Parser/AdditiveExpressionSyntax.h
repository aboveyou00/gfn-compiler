#pragma once
#include "Parser/BinaryExpressionSyntax.h"

#include <vector>

class AdditiveExpressionSyntax :
    public BinaryExpressionSyntax
{
public:
    AdditiveExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *lhs, ExpressionSyntax *rhs, const std::string op);
    ~AdditiveExpressionSyntax();

    static ExpressionSyntax *tryParse(Cursor<Token*> &cursor);

    virtual void emit(std::vector<Opcode*> &ops) const override;

private:
    static AdditiveExpressionSyntax *tryParseRhs(Cursor<Token*> &cursor, ExpressionSyntax *lhs);
};
