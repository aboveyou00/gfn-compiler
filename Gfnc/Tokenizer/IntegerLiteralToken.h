#pragma once

#include "Tokenizer/Token.h"

class IntegerLiteralToken :
    public Token
{
public:
    IntegerLiteralToken(uint32_t start, uint32_t size, uint64_t value);
    ~IntegerLiteralToken();

    virtual bool isIntLiteral() const override;
    virtual uint64_t intLiteral() const override;

    virtual void repr(std::stringstream &stream) const override;

private:
    uint64_t m_value;
};
