#pragma once

#include "Tokenizer/Token.h"

class IdentifierToken :
    public Token
{
public:
    IdentifierToken(uint32_t start, uint32_t size, std::string ident);
    ~IdentifierToken();

    virtual bool isIdentifier() const override;
    virtual std::string identifier() const override;

    virtual void repr(std::stringstream &stream) const override;

private:
    std::string m_ident;
};
