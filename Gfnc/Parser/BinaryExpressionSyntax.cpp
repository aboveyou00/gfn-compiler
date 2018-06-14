#include "stdafx.h"
#include "Parser/BinaryExpressionSyntax.h"

#include "Runtime/RuntimeType.h"
#include "Runtime/MethodGroup.h"
#include "Runtime/MethodOverload.h"

namespace Gfn::Compiler::Parser
{
    BinaryExpressionSyntax::BinaryExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *lhs, ExpressionSyntax *rhs, const std::string op)
        : ExpressionSyntax(startIndex, length), m_lhs(lhs), m_rhs(rhs), m_op(op), m_selectedOperatorOverload(nullptr)
    {
    }
    BinaryExpressionSyntax::~BinaryExpressionSyntax()
    {
        SafeDelete(this->m_lhs);
        SafeDelete(this->m_rhs);
    }

    ExpressionSyntax *BinaryExpressionSyntax::lhs() const
    {
        return this->m_lhs;
    }
    ExpressionSyntax *BinaryExpressionSyntax::rhs() const
    {
        return this->m_rhs;
    }
    const std::string BinaryExpressionSyntax::op() const
    {
        return this->m_op;
    }

    bool BinaryExpressionSyntax::tryResolveType()
    {
        if (this->m_resolvedType != nullptr) return true;

        if (!this->lhs()->tryResolveType()) return false;
        if (!this->rhs()->tryResolveType()) return false;

        auto leftType = this->lhs()->resolvedType();
        auto rightType = this->rhs()->resolvedType();

        auto operatorMethodName = this->getOperatorMethodName();
        Runtime::MethodGroup *methods;

        {
            methods = leftType->getStaticMethods(operatorMethodName);
            if (methods != nullptr)
            {
                this->m_selectedOperatorOverload = methods->findOverload({ leftType, rightType });
            }
        }

        if (!this->m_selectedOperatorOverload)
        {
            methods = rightType->getStaticMethods(operatorMethodName);
            if (methods != nullptr)
            {
                this->m_selectedOperatorOverload = methods->findOverload({ leftType, rightType });
            }
        }

        if (this->m_selectedOperatorOverload == nullptr) return false;
        this->m_resolvedType = this->m_selectedOperatorOverload->returnType();
        return true;
    }

    void BinaryExpressionSyntax::emit(Emit::MethodBuilder &mb) const
    {
        this->assertTypeIsResolved();

        this->lhs()->emit(mb);
        this->rhs()->emit(mb);

        this->m_selectedOperatorOverload->emitInvoke(mb);
    }

    void BinaryExpressionSyntax::repr(std::stringstream &stream) const
    {
        stream << this->lhs() << " "s << this->op() << " "s << this->rhs();
    }
}
