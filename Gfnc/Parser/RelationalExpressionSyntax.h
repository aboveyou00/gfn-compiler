#pragma once
#include "Parser/BinaryExpressionSyntax.h"

#include <vector>

namespace Gfn::Compiler::Parser
{
    class RelationalExpressionSyntax :
        public BinaryExpressionSyntax
    {
    public:
        static ExpressionSyntax *tryParse(Cursor<Tokenizer::Token*> &cursor);

    private:
        static RelationalExpressionSyntax *tryParseRhs(Cursor<Tokenizer::Token*> &cursor, ExpressionSyntax *lhs);

    public:
        RelationalExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *lhs, ExpressionSyntax *rhs, const std::string op);
        ~RelationalExpressionSyntax();

    protected:
        virtual std::string getOperatorMethodName() const override;
    };
}
