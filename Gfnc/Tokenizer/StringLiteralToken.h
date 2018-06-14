#pragma once

#include "Tokenizer/Token.h"

namespace Gfn::Compiler::Tokenizer
{
    class StringLiteralToken :
        public Token
    {
    public:
        StringLiteralToken(uint32_t start, uint32_t size, std::string value);
        ~StringLiteralToken();

        virtual bool isStringLiteral() const override;
        virtual const std::string &stringLiteral() const override;

        virtual void repr(std::stringstream &stream) const override;

    private:
        std::string m_value;
    };
}
