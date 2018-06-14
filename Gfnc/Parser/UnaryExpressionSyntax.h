#pragma once
#include "Parser/ExpressionSyntax.h"

namespace Gfn::Compiler::Runtime
{
    class MethodOverload;
}

namespace Gfn::Compiler::Parser
{
    class UnaryExpressionSyntax :
        public ExpressionSyntax
    {
    public:
        static ExpressionSyntax *tryParse(Cursor<Tokenizer::Token*> &cursor);

    public:
        UnaryExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *expr, const std::string op);
        ~UnaryExpressionSyntax();

        ExpressionSyntax *expr() const;
        const std::string op() const;

        virtual bool tryResolveType() override;

        virtual void emit(Emit::MethodBuilder &mb) const override;

        virtual void repr(std::stringstream &stream) const;

    protected:
        virtual std::string getOperatorMethodName() const;

    private:
        ExpressionSyntax *m_expr;
        const std::string m_op;

        Runtime::MethodOverload *m_selectedOperatorOverload;

        bool isNegativeNumericLimit() const;
    };
}
