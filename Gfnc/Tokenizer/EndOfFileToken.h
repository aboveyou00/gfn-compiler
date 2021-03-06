#pragma once
#include "Tokenizer/Token.h"

namespace Gfn::Compiler::Tokenizer
{
    class EndOfFileToken :
        public Token
    {
    public:
        EndOfFileToken(uint32_t startIndex);
        ~EndOfFileToken();

        virtual bool isEndOfFile() const override;

        virtual void repr(std::stringstream &stream) const override;
    };
}
