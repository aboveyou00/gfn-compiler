#include "stdafx.h"

#include "Parser/IfStatementSyntax.h"

#include "Tokenizer/Token.h"
#include "Parser/ExpressionSyntax.h"
#include "Emit/MethodBuilder.h"

IfStatementSyntax *IfStatementSyntax::tryParse(Cursor<Token*> &cursor)
{
    if (!cursor.current()->isKeyword() || cursor.current()->keyword() != "if"s) return nullptr;

    auto startIndex = cursor.snapshot();
    cursor.next();

    if (!cursor.current()->isOperator() || cursor.current()->op() != "("s)
    {
        cursor.reset(startIndex);
        return nullptr;
    }
    cursor.next();

    ExpressionSyntax *condition = tryParseSyntax<ExpressionSyntax>(cursor);
    if (condition == nullptr)
    {
        cursor.reset(startIndex);
        return nullptr;
    }

    if (!cursor.current()->isOperator() || cursor.current()->op() != ")"s)
    {
        cursor.reset(startIndex);
        return nullptr;
    }
    cursor.next();

    StatementSyntax *ifBody = StatementSyntax::tryParse(cursor);
    if (ifBody == nullptr)
    {
        cursor.reset(startIndex);
        return nullptr;
    }

    StatementSyntax *elseBody = nullptr;
    if (cursor.current()->isKeyword() && cursor.current()->keyword() == "else"s)
    {
        cursor.next();
        elseBody = StatementSyntax::tryParse(cursor);
        if (elseBody == nullptr)
        {
            cursor.reset(startIndex);
            return nullptr;
        }
    }

    return new IfStatementSyntax(startIndex, cursor.snapshot() - startIndex, condition, ifBody, elseBody);
}

IfStatementSyntax::IfStatementSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *condition, StatementSyntax *ifBody, StatementSyntax *elseBody)
    : StatementSyntax(startIndex, length), m_condition(condition), m_ifBody(ifBody), m_elseBody(elseBody)
{
}
IfStatementSyntax::~IfStatementSyntax()
{
}

ExpressionSyntax *IfStatementSyntax::condition() const
{
    return this->m_condition;
}
StatementSyntax *IfStatementSyntax::ifBody() const
{
    return this->m_ifBody;
}
StatementSyntax *IfStatementSyntax::elseBody() const
{
    return this->m_elseBody;
}

bool IfStatementSyntax::tryResolveTypes()
{
    auto worked = true;

    //TODO: suggest boolean type to condition
    if (!this->condition()->tryResolveType()) worked = false;
    //TODO: verify condition type is implicitly convertible to boolean

    //TODO MAYBE: only resolve if and else body types if the condition is resolved
    if (!this->ifBody()->tryResolveTypes()) worked = false;
    if (this->elseBody() != nullptr && !this->elseBody()->tryResolveTypes()) worked = false;

    return worked;
}
void IfStatementSyntax::assertTypesAreResolved() const
{
    throw std::logic_error("Not implemented"s);
}

void IfStatementSyntax::emit(MethodBuilder&) const
{
    throw std::logic_error("Not implemented"s);
}

void IfStatementSyntax::repr(std::stringstream &stream) const
{
    stream << "if ("s << this->condition() << ") "s << this->ifBody();
    auto elseBody = this->elseBody();
    if (elseBody != nullptr) stream << " else "s << elseBody;
}
