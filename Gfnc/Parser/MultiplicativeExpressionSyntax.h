#pragma once
#include "Parser/BinaryExpressionSyntax.h"

#include <vector>

namespace Gfn::Compiler::Parser
{
    class MultiplicativeExpressionSyntax :
        public BinaryExpressionSyntax
    {
    public:
        static ExpressionSyntax *tryParse(Cursor<Tokenizer::Token*> &cursor);

    private:
        static MultiplicativeExpressionSyntax *tryParseRhs(Cursor<Tokenizer::Token*> &cursor, ExpressionSyntax *lhs);

    public:
        MultiplicativeExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *lhs, ExpressionSyntax *rhs, const std::string op);
        ~MultiplicativeExpressionSyntax();

    protected:
        virtual std::string getOperatorMethodName() const override;
    };
}
