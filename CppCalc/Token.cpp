#include "stdafx.h"

#include "Token.h"

Token::Token(uint32_t startIndex, uint32_t length)
    : m_startIndex(startIndex), m_length(length)
{
}
Token::~Token()
{
}

uint32_t Token::startIndex() const
{
    return this->m_startIndex;
}
uint32_t Token::length() const
{
    return this->m_length;
}
uint32_t Token::endIndex() const
{
    return this->m_startIndex + this->m_length;
}

bool Token::isIntLiteral() const
{
    return false;
}
uint64_t Token::intLiteral() const
{
    throw std::logic_error("This token is not an integer literal!");
}

bool Token::isOperator() const
{
    return false;
}
const std::string &Token::op() const
{
    throw std::logic_error("This token is not an operator!");
}

bool Token::isEndOfFile() const
{
    return false;
}

std::string Token::stringify() const
{
    thread_local static std::stringstream buffer;
    buffer.clear();
    this->stringify(buffer);
    return buffer.str();
}

void Token::stringify(std::stringstream &stream) const
{
    stream << "[" << this->startIndex() << ", " << this->endIndex() << ") ";
    this->repr(stream);
}

std::stringstream &operator<<(std::stringstream &stream, const Token &tok)
{
    tok.repr(stream);
}
std::ostream &operator<<(std::ostream &stream, const Token &tok)
{
    thread_local static std::stringstream sstream;
    sstream.clear();
    sstream << tok;
    stream << sstream.str();
}
