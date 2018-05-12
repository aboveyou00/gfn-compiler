#include "stdafx.h"
#include "PrimaryExpressionSyntax.h"

#include "ExpressionSyntax.h"
#include "Token.h"

PrimaryExpressionSyntax::PrimaryExpressionSyntax(uint32_t startIndex, uint32_t length, PrimaryExpressionType type)
    : ExpressionSyntax(startIndex, length), m_type(type)
{
}
PrimaryExpressionSyntax::PrimaryExpressionSyntax(uint32_t startIndex, uint32_t length, uint64_t intLiteralValue)
    : PrimaryExpressionSyntax(startIndex, length, PrimaryExpressionType::IntegerLiteral)
{
    this->m_intLiteralValue = intLiteralValue;
}
PrimaryExpressionSyntax::~PrimaryExpressionSyntax()
{
}

PrimaryExpressionType PrimaryExpressionSyntax::type() const
{
    return this->m_type;
}

uint64_t PrimaryExpressionSyntax::intLiteralValue() const
{
    if (this->type() != PrimaryExpressionType::IntegerLiteral) throw std::logic_error("Can't get int literal value. This primary expression is not an integer literal!"s);
    return this->m_intLiteralValue;
}

ExpressionSyntax *PrimaryExpressionSyntax::tryParse(Cursor<Token*> &cursor)
{
    auto startIndex = cursor.snapshot();
    auto current = cursor.current();
    
    if (current->isIntLiteral())
    {
        cursor.next();
        return new PrimaryExpressionSyntax(startIndex, 1, current->intLiteral());
    }

    if (current->isOperator() && current->op() == "("s)
    {
        cursor.next();
        auto expr = tryParseSyntax<ExpressionSyntax>(cursor);
        if (expr != nullptr && cursor.current()->isOperator() && cursor.current()->op() == ")"s)
        {
            cursor.next();
            return expr;
        }
        else
        {
            cursor.reset(startIndex);
            delete expr;
        }
    }

    return nullptr;
}

void PrimaryExpressionSyntax::repr(std::stringstream &stream) const
{
    switch (this->type())
    {
    case PrimaryExpressionType::IntegerLiteral:
        stream << this->intLiteralValue();
        return;

    default:
        throw std::logic_error("Can't repr primary expression syntax. Unknown primary expression type"s);
    }
}
