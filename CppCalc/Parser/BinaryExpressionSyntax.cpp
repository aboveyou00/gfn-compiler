#include "stdafx.h"
#include "Parser/BinaryExpressionSyntax.h"

BinaryExpressionSyntax::BinaryExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *lhs, ExpressionSyntax *rhs, const std::string op)
    : ExpressionSyntax(startIndex, length), m_lhs(lhs), m_rhs(rhs), m_op(op)
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

void BinaryExpressionSyntax::emit(std::vector<Opcode*> &ops) const
{
    this->lhs()->emit(ops);
    this->rhs()->emit(ops);

    auto operatorMethodName = this->getOperatorMethodName();

    throw std::logic_error("Not implemented"s);
}

void BinaryExpressionSyntax::repr(std::stringstream &stream) const
{
    stream << this->lhs() << " "s << this->op() << " "s << this->rhs();
}
