#include "stdafx.h"

#include "Tokenizer/OperatorToken.h"

OperatorToken::OperatorToken(uint32_t startIndex, uint32_t length, std::string op)
    : Token(startIndex, length), m_op(op)
{
}
OperatorToken::~OperatorToken()
{
}

bool OperatorToken::isOperator() const
{
    return true;
}
const std::string &OperatorToken::op() const
{
    return this->m_op;
}

void OperatorToken::repr(std::stringstream &stream) const
{
    stream << this->op();
}
