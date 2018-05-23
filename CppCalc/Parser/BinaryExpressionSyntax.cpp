#include "stdafx.h"
#include "Parser/BinaryExpressionSyntax.h"

#include "Runtime/RuntimeType.h"
#include "Runtime/MethodGroup.h"
#include "Runtime/MethodOverload.h"

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
    MethodGroup *methods;

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

void BinaryExpressionSyntax::emit(std::vector<Opcode*> &ops) const
{
    this->assertTypeIsResolved();

    this->lhs()->emit(ops);
    this->rhs()->emit(ops);

    this->m_selectedOperatorOverload->emitInvoke(ops);
}

void BinaryExpressionSyntax::repr(std::stringstream &stream) const
{
    stream << this->lhs() << " "s << this->op() << " "s << this->rhs();
}
