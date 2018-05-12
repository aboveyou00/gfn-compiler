#include "stdafx.h"

#include "UnaryExpressionSyntax.h"

#include "PrimaryExpressionSyntax.h"
#include "Token.h"

UnaryExpressionSyntax::UnaryExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *expr, const std::string op)
    : ExpressionSyntax(startIndex, length), m_expr(expr), m_op(op)
{
}
UnaryExpressionSyntax::~UnaryExpressionSyntax()
{
}

ExpressionSyntax *UnaryExpressionSyntax::tryParse(Cursor<Token*> &cursor)
{
    if (cursor.current()->isOperator())
    {
        auto op = cursor.current()->op();
        if (op == "+" || op == "-")
        {
            auto beginIndex = cursor.snapshot();
            cursor.next();
            ExpressionSyntax *rhs = tryParseSyntax<UnaryExpressionSyntax>(cursor);
            if (rhs == nullptr) cursor.reset(beginIndex);
            else return new UnaryExpressionSyntax(beginIndex, cursor.snapshot() - beginIndex, rhs, op);
        }
    }

    return tryParseSyntax<PrimaryExpressionSyntax>(cursor);
}

ExpressionSyntax *UnaryExpressionSyntax::expr() const
{
    return this->m_expr;
}
const std::string UnaryExpressionSyntax::op() const
{
    return this->m_op;
}

void UnaryExpressionSyntax::repr(std::stringstream &stream) const
{
    stream << this->m_op << this->expr();
}
