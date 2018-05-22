#pragma once
#include "Parser/BinaryExpressionSyntax.h"

#include <vector>

class ConditionalAndExpressionSyntax :
    public BinaryExpressionSyntax
{
public:
    static ExpressionSyntax *tryParse(Cursor<Token*> &cursor);

private:
    static ConditionalAndExpressionSyntax *tryParseRhs(Cursor<Token*> &cursor, ExpressionSyntax *lhs);

public:
    ConditionalAndExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *lhs, ExpressionSyntax *rhs, const std::string op);
    ~ConditionalAndExpressionSyntax();

    virtual void emit(std::vector<Opcode*> &ops) const override;

protected:
    virtual std::string getOperatorMethodName() const override;
};
