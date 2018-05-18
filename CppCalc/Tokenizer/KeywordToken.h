#pragma once

#include "Tokenizer/Token.h"

class KeywordToken :
    public Token
{
public:
    KeywordToken(uint32_t start, uint32_t size, std::string keyword);
    ~KeywordToken();

    virtual bool isKeyword() const override;
    virtual std::string keyword() const override;

    virtual void repr(std::stringstream &stream) const override;

private:
    std::string m_keyword;
};
