#include "stdafx.h"
#include "Tokenizer/BooleanLiteralToken.h"

BooleanLiteralToken::BooleanLiteralToken(uint32_t start, uint32_t size, std::string keyword)
    : KeywordToken(start, size, keyword), m_value(keyword == "true"s)
{
}
BooleanLiteralToken::~BooleanLiteralToken()
{
}

bool BooleanLiteralToken::isBooleanLiteral() const
{
    return true;
}
bool BooleanLiteralToken::booleanLiteral() const
{
    return this->m_value;
}
