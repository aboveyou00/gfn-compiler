#include "stdafx.h"
#include "Parser/PrimaryExpressionSyntax.h"

#include "Parser/ExpressionSyntax.h"
#include "Tokenizer/Token.h"
#include "Emit/MethodBuilder.h"
#include "Emit/OpLdcI4.h"
#include "Runtime/RuntimeType.h"

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

    if (current->isStringLiteral())
    {
        cursor.next();
        return new PrimaryExpressionSyntax(current->startIndex(), current->length(), current->stringLiteral());
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

PrimaryExpressionSyntax::PrimaryExpressionSyntax(uint32_t startIndex, uint32_t length, PrimaryExpressionType type)
    : ExpressionSyntax(startIndex, length), m_type(type)
{
}
PrimaryExpressionSyntax::PrimaryExpressionSyntax(uint32_t startIndex, uint32_t length, uint64_t intLiteralValue)
    : PrimaryExpressionSyntax(startIndex, length, PrimaryExpressionType::IntegerLiteral)
{
    this->m_intLiteralValue = intLiteralValue;
}
PrimaryExpressionSyntax::PrimaryExpressionSyntax(uint32_t startIndex, uint32_t length, const std::string &stringLiteralValue)
    : PrimaryExpressionSyntax(startIndex, length, PrimaryExpressionType::StringLiteral)
{
    this->m_stringLiteralValue = stringLiteralValue;
}
PrimaryExpressionSyntax::PrimaryExpressionSyntax(uint32_t startIndex, uint32_t length, bool booleanLiteralValue)
    : PrimaryExpressionSyntax(startIndex, length, PrimaryExpressionType::BooleanLiteral)
{
    this->m_intLiteralValue = booleanLiteralValue ? 1 : 0;
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
const std::string &PrimaryExpressionSyntax::stringLiteralValue() const
{
    if (this->type() != PrimaryExpressionType::StringLiteral) throw std::logic_error("Can't get string literal value. This primary expression is not a string literal!"s);
    return this->m_stringLiteralValue;
}
bool PrimaryExpressionSyntax::booleanLiteralValue() const
{
    if (this->type() != PrimaryExpressionType::BooleanLiteral) throw std::logic_error("Can't get boolean literal value. This primary expression is not a boolean literal!"s);
    return this->m_intLiteralValue == 1;
}

bool PrimaryExpressionSyntax::tryResolveType()
{
    if (this->m_resolvedType != nullptr) return true;
    
    switch (this->type())
    {
    case PrimaryExpressionType::IntegerLiteral:
        this->m_resolvedType = RuntimeType::int32();
        return true;

    case PrimaryExpressionType::StringLiteral:
        this->m_resolvedType = RuntimeType::string();
        return true;
        
    case PrimaryExpressionType::BooleanLiteral:
        this->m_resolvedType = RuntimeType::boolean();
        return true;

    default:
        throw std::logic_error("Can't emit primary expression syntax. Unknown primary expression type"s);
    }
}

void PrimaryExpressionSyntax::emit(MethodBuilder &mb) const
{
    this->assertTypeIsResolved();

    switch (this->type())
    {
    case PrimaryExpressionType::IntegerLiteral:
        {
            auto val = this->intLiteralValue();
            //Note: negative integer literals are handled in a special case in UnaryExpressionSyntax when op == "-"
            if (val > std::numeric_limits<int32_t>::max()) throw std::logic_error("Integer literal does not fit in int32_t."s);
            mb.addOpcode(new OpLdcI4((int32_t)val));
        }
        break;
        
    case PrimaryExpressionType::StringLiteral:
        {
            auto &val = this->stringLiteralValue();
            throw std::logic_error("Not implemented"s);
        }
        break;
        
    case PrimaryExpressionType::BooleanLiteral:
        {
            auto val = this->booleanLiteralValue();
            mb.addOpcode(new OpLdcI4(val ? 1 : 0));
        }
        break;

    default:
        throw std::logic_error("Can't emit primary expression syntax. Unknown primary expression type"s);
    }
}

void PrimaryExpressionSyntax::repr(std::stringstream &stream) const
{
    switch (this->type())
    {
    case PrimaryExpressionType::IntegerLiteral:
        stream << this->intLiteralValue();
        return;

    case PrimaryExpressionType::StringLiteral:
        stream << "\""s << this->stringLiteralValue() << "\""s;
        return;

    case PrimaryExpressionType::BooleanLiteral:
        stream << (this->booleanLiteralValue() ? "true"s : "false"s);
        return;

    default:
        throw std::logic_error("Can't repr primary expression syntax. Unknown primary expression type"s);
    }
}
