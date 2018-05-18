#include "stdafx.h"
#include "Tokenizer/KeywordToken.h"

KeywordToken::KeywordToken(uint32_t start, uint32_t size, std::string keyword)
    : Token(start, size), m_keyword(keyword)
{
}
KeywordToken::~KeywordToken()
{
}

bool KeywordToken::isKeyword() const
{
    return true;
}
std::string KeywordToken::keyword() const
{
    return this->m_keyword;
}

void KeywordToken::repr(std::stringstream &stream) const
{
    stream << this->keyword();
}
