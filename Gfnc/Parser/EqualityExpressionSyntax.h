#pragma once
#include "Parser/BinaryExpressionSyntax.h"

#include <vector>

namespace Gfn::Compiler::Parser
{
    class EqualityExpressionSyntax :
        public BinaryExpressionSyntax
    {
    public:
        static ExpressionSyntax *tryParse(Cursor<Tokenizer::Token*> &cursor);

    private:
        static EqualityExpressionSyntax *tryParseRhs(Cursor<Tokenizer::Token*> &cursor, ExpressionSyntax *lhs);

    public:
        EqualityExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *lhs, ExpressionSyntax *rhs, const std::string op);
        ~EqualityExpressionSyntax();

    protected:
        virtual std::string getOperatorMethodName() const override;
    };
}
