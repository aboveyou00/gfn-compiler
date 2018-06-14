#pragma once
#include "Parser/StatementSyntax.h"

namespace Gfn::Compiler::Parser
{
    class ExpressionSyntax;

    class ExpressionStatementSyntax :
        public StatementSyntax
    {
    public:
        static ExpressionStatementSyntax *tryParse(Cursor<Tokenizer::Token*> &cursor);

    public:
        ExpressionStatementSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *expr);
        ~ExpressionStatementSyntax();

        ExpressionSyntax *expr() const;

        virtual bool tryResolveTypes() override;
        virtual void assertTypesAreResolved() const override;

        virtual void emit(Runtime::MethodBuilder &mb) const override;

        virtual void repr(std::stringstream &stream) const;

    private:
        ExpressionSyntax *m_expr;
    };
}
