#include "stdafx.h"
#include "Tokenizer/IdentifierToken.h"

IdentifierToken::IdentifierToken(uint32_t start, uint32_t size, std::string ident)
    : Token(start, size), m_ident(ident)
{
}
IdentifierToken::~IdentifierToken()
{
}

bool IdentifierToken::isIdentifier() const
{
    return true;
}
std::string IdentifierToken::identifier() const
{
    return this->m_ident;
}

void IdentifierToken::repr(std::stringstream &stream) const
{
    stream << this->identifier();
}
