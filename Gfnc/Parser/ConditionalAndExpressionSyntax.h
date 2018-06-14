#pragma once
#include "Parser/BinaryExpressionSyntax.h"

#include <vector>

namespace Gfn::Compiler::Parser
{
    class ConditionalAndExpressionSyntax :
        public BinaryExpressionSyntax
    {
    public:
        static ExpressionSyntax *tryParse(Cursor<Tokenizer::Token*> &cursor);

    private:
        static ConditionalAndExpressionSyntax *tryParseRhs(Cursor<Tokenizer::Token*> &cursor, ExpressionSyntax *lhs);

    public:
        ConditionalAndExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *lhs, ExpressionSyntax *rhs, const std::string op);
        ~ConditionalAndExpressionSyntax();

        virtual bool tryResolveType() override;

        virtual void emit(Emit::MethodBuilder &mb) const override;

    protected:
        virtual std::string getOperatorMethodName() const override;
    };
}
