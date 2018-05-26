#include "stdafx.h"
#include "Tokenizer/StringLiteralToken.h"

StringLiteralToken::StringLiteralToken(uint32_t start, uint32_t size, std::string value)
    : Token(start, size), m_value(value)
{
}
StringLiteralToken::~StringLiteralToken()
{
}

bool StringLiteralToken::isStringLiteral() const
{
    return true;
}
std::string StringLiteralToken::stringLiteral() const
{
    return this->m_value;
}

void StringLiteralToken::repr(std::stringstream &stream) const
{
    stream << this->keyword();
}
