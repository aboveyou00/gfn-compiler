#pragma once

#include "Tokenizer/KeywordToken.h"

class BooleanLiteralToken :
    public KeywordToken
{
public:
    BooleanLiteralToken(uint32_t start, uint32_t size, std::string keyword);
    ~BooleanLiteralToken();

    virtual bool isBooleanLiteral() const override;
    virtual bool booleanLiteral() const override;

private:
    bool m_value;
};
