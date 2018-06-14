#pragma once

#include "Parser/Syntax.h"

namespace Gfn::Compiler::Tokenizer
{
    class Token;
}

namespace Gfn::Compiler::Runtime
{
    class MethodBuilder;
}

namespace Gfn::Compiler::Parser
{
    class StatementSyntax
        : public Syntax
    {
    public:
        static StatementSyntax *tryParse(Cursor<Tokenizer::Token*> &cursor);

    public:
        StatementSyntax(uint32_t startIndex, uint32_t length);
        ~StatementSyntax();

        virtual bool tryResolveTypes() = 0;
        virtual void assertTypesAreResolved() const = 0;

        virtual void emit(Runtime::MethodBuilder &mb) const = 0;
    };
}
