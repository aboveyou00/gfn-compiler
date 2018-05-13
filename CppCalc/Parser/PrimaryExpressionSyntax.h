#pragma once
#include "Parser/ExpressionSyntax.h"

enum class PrimaryExpressionType
{
    IntegerLiteral = 1
};

class PrimaryExpressionSyntax :
    public ExpressionSyntax
{
private:
    PrimaryExpressionSyntax(uint32_t startIndex, uint32_t length, PrimaryExpressionType type);
public:
    PrimaryExpressionSyntax(uint32_t startIndex, uint32_t length, uint64_t intLiteralValue);
    ~PrimaryExpressionSyntax();

    static ExpressionSyntax *tryParse(Cursor<Token*> &cursor);

    PrimaryExpressionType type() const;

    uint64_t intLiteralValue() const;

    virtual void emit(std::vector<Opcode*> &ops) const override;

    virtual void repr(std::stringstream &stream) const;

private:
    PrimaryExpressionType m_type;
    uint64_t m_intLiteralValue;
};
