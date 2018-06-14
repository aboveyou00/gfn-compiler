#pragma once
#include "Parser/ExpressionSyntax.h"

namespace Gfn::Compiler::Runtime
{
    class MethodOverload;
}

namespace Gfn::Compiler::Parser
{
    class BinaryExpressionSyntax :
        public ExpressionSyntax
    {
    public:
        BinaryExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *lhs, ExpressionSyntax *rhs, const std::string op);
        ~BinaryExpressionSyntax();

        ExpressionSyntax *lhs() const;
        ExpressionSyntax *rhs() const;
        const std::string op() const;

        virtual bool tryResolveType() override;

        virtual void emit(Emit::MethodBuilder &mb) const override;

        virtual void repr(std::stringstream &stream) const;

    protected:
        virtual std::string getOperatorMethodName() const = 0;

    private:
        ExpressionSyntax *m_lhs;
        ExpressionSyntax *m_rhs;
        const std::string m_op;

        Runtime::MethodOverload *m_selectedOperatorOverload;
    };
}
