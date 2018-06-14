#pragma once

#include "Parser/Syntax.h"

namespace Gfn::Compiler::Tokenizer
{
    class Token;
}

namespace Gfn::Compiler::Runtime
{
    class RuntimeType;
}

namespace Gfn::Compiler::Emit
{
    class MethodBuilder;
}

namespace Gfn::Compiler::Parser
{
    class ExpressionSyntax
        : public Syntax
    {
    public:
        static ExpressionSyntax *tryParse(Cursor<Tokenizer::Token*> &cursor);

    public:
        ExpressionSyntax(uint32_t startIndex, uint32_t length);
        ~ExpressionSyntax();

        virtual bool tryResolveType() = 0;
        Runtime::RuntimeType *resolvedType();
        void assertTypeIsResolved() const;

        virtual void emit(Emit::MethodBuilder &mb) const = 0;

    protected:
        Runtime::RuntimeType *m_resolvedType;
    };

    template <typename T>
    inline ExpressionSyntax *tryParseSyntax(Cursor<Tokenizer::Token*> &cursor)
    {
        static_assert(std::is_base_of<ExpressionSyntax, T>::value, "tryParseSyntax only works on types that extend ExpressionSyntax");
        return T::tryParse(cursor);
    }
    template <typename T>
    inline ExpressionSyntax *parseSyntax(Cursor<Tokenizer::Token*> &cursor)
    {
        auto result = tryParseSyntax<T>(cursor);
        if (result == nullptr) throw std::logic_error("Failed to parse syntax."s);
        return result;
    }
}
