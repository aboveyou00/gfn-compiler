#include "stdafx.h"
#include "Tokenizer/IntegerLiteralToken.h"

namespace Gfn::Compiler::Tokenizer
{
    IntegerLiteralToken::IntegerLiteralToken(uint32_t start, uint32_t size, uint64_t value)
        : Token(start, size), m_value(value)
    {
    }
    IntegerLiteralToken::~IntegerLiteralToken()
    {
    }

    bool IntegerLiteralToken::isIntLiteral() const
    {
        return true;
    }
    uint64_t IntegerLiteralToken::intLiteral() const
    {
        return this->m_value;
    }

    void IntegerLiteralToken::repr(std::stringstream &stream) const
    {
        stream << this->intLiteral();
    }
}
