#pragma once
#include "Parser/BinaryExpressionSyntax.h"

#include <vector>

class EqualityExpressionSyntax :
    public BinaryExpressionSyntax
{
public:
    EqualityExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *lhs, ExpressionSyntax *rhs, const std::string op);
    ~EqualityExpressionSyntax();

    static ExpressionSyntax *tryParse(Cursor<Token*> &cursor);

    virtual void emit(std::vector<Opcode*> &ops) const override;

private:
    static EqualityExpressionSyntax *tryParseRhs(Cursor<Token*> &cursor, ExpressionSyntax *lhs);
};
