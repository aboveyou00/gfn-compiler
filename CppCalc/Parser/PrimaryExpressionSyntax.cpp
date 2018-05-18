#include "stdafx.h"
#include "Parser/PrimaryExpressionSyntax.h"

#include "Parser/ExpressionSyntax.h"
#include "Tokenizer/Token.h"
#include "Emit/OpLdcI4.h"

PrimaryExpressionSyntax::PrimaryExpressionSyntax(uint32_t startIndex, uint32_t length, PrimaryExpressionType type)
    : ExpressionSyntax(startIndex, length), m_type(type)
{
}
PrimaryExpressionSyntax::PrimaryExpressionSyntax(uint32_t startIndex, uint32_t length, uint64_t intLiteralValue)
    : PrimaryExpressionSyntax(startIndex, length, PrimaryExpressionType::IntegerLiteral)
{
    this->m_intLiteralValue = intLiteralValue;
}
PrimaryExpressionSyntax::PrimaryExpressionSyntax(uint32_t startIndex, uint32_t length, bool booleanLiteralValue)
    : PrimaryExpressionSyntax(startIndex, length, PrimaryExpressionType::BooleanLiteral)
{
    this->m_intLiteralValue = booleanLiteralValue ? 1 : 0;
}
PrimaryExpressionSyntax::~PrimaryExpressionSyntax()
{
}

ExpressionSyntax *PrimaryExpressionSyntax::tryParse(Cursor<Token*> &cursor)
{
    auto current = cursor.current();
    auto snapshot = cursor.snapshot();

    if (current->isIntLiteral())
    {
        cursor.next();
        return new PrimaryExpressionSyntax(current->startIndex(), current->length(), current->intLiteral());
    }

    if (current->isBooleanLiteral())
    {
        cursor.next();
        return new PrimaryExpressionSyntax(current->startIndex(), current->length(), current->booleanLiteral());
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
            cursor.reset(snapshot);
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

bool PrimaryExpressionSyntax::booleanLiteralValue() const
{
    if (this->type() != PrimaryExpressionType::BooleanLiteral) throw std::logic_error("Can't get boolean literal value. This primary expression is not a boolean literal!"s);
    return this->m_intLiteralValue == 1;
}

void PrimaryExpressionSyntax::emit(std::vector<Opcode*> &ops) const
{
    switch (this->type())
    {
    case PrimaryExpressionType::IntegerLiteral:
        {
            auto val = this->intLiteralValue();
            //Note: negative integer literals are handled in a special case in UnaryExpressionSyntax when op == "-"
            if (val > std::numeric_limits<int32_t>::max()) throw std::logic_error("Integer literal does not fit in int32_t.");
            ops.push_back(new OpLdcI4((int32_t)val));
        }
        break;
        
    case PrimaryExpressionType::BooleanLiteral:
        {
            auto val = this->booleanLiteralValue();
            ops.push_back(new OpLdcI4(val ? 1 : 0));
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

    case PrimaryExpressionType::BooleanLiteral:
        stream << this->booleanLiteralValue();
        return;

    default:
        throw std::logic_error("Can't repr primary expression syntax. Unknown primary expression type"s);
    }
}
