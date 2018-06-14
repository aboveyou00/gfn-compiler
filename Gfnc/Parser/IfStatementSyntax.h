#pragma once
#include "Parser/StatementSyntax.h"

namespace Gfn::Compiler::Parser
{
    class ExpressionSyntax;

    class IfStatementSyntax :
        public StatementSyntax
    {
    public:
        static IfStatementSyntax *tryParse(Cursor<Tokenizer::Token*> &cursor);

    public:
        IfStatementSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *condition, StatementSyntax *ifBody, StatementSyntax *elseBody = nullptr);
        ~IfStatementSyntax();

        ExpressionSyntax *condition() const;
        StatementSyntax *ifBody() const;
        StatementSyntax *elseBody() const;

        virtual bool tryResolveTypes() override;
        virtual void assertTypesAreResolved() const override;

        virtual void emit(Runtime::MethodBuilder &mb) const override;

        virtual void repr(std::stringstream &stream) const;

    private:
        ExpressionSyntax *m_condition;
        StatementSyntax *m_ifBody, *m_elseBody;
    };
}
