#pragma once
#include "Parser/BinaryExpressionSyntax.h"

#include <vector>

namespace Gfn::Compiler::Parser
{
    class ConditionalOrExpressionSyntax :
        public BinaryExpressionSyntax
    {
    public:
        static ExpressionSyntax *tryParse(Cursor<Tokenizer::Token*> &cursor);

    private:
        static ConditionalOrExpressionSyntax *tryParseRhs(Cursor<Tokenizer::Token*> &cursor, ExpressionSyntax *lhs);

    public:
        ConditionalOrExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *lhs, ExpressionSyntax *rhs, const std::string op);
        ~ConditionalOrExpressionSyntax();

        virtual bool tryResolveType() override;

        virtual void emit(Emit::MethodBuilder &mb) const override;

    protected:
        virtual std::string getOperatorMethodName() const override;
    };
}
