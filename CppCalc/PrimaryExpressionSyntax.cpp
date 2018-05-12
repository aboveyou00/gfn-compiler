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

PrimaryExpressionType PrimaryExpressionSyntax::type() const
{
    return this->m_type;
}

uint64_t PrimaryExpressionSyntax::intLiteralValue() const
{
    if (this->type() != PrimaryExpressionType::IntegerLiteral) throw std::logic_error("Can't get int literal value. This primary expression is not an integer literal!"s);
    return this->m_intLiteralValue;
}

void PrimaryExpressionSyntax::eval(std::stack<int32_t> &stack) const
{
    switch (this->type())
    {
    case PrimaryExpressionType::IntegerLiteral:
        {
            auto val = this->intLiteralValue();
            //Note: negative integer literals are handled in a special case in UnaryExpressionSyntax when op == "-"
            if (val > std::numeric_limits<uint32_t>::max()) throw std::logic_error("Integer literal does not fit in uint32_t.");
            stack.push((uint32_t)val);
        }
        break;

    default:
        throw std::logic_error("Can't repr primary expression syntax. Unknown primary expression type"s);
    }
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
