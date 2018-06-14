#include "stdafx.h"

#include "Parser/PrintStatementSyntax.h"

#include "Tokenizer/Token.h"
#include "Parser/ExpressionSyntax.h"
#include "Emit/MethodBuilder.h"

PrintStatementSyntax *PrintStatementSyntax::tryParse(Cursor<Token*> &cursor)
{
    if (!cursor.current()->isKeyword() || (cursor.current()->keyword() != "print"s && cursor.current()->keyword() != "puts"s)) return nullptr;

    auto isPuts = cursor.current()->keyword() == "puts"s;

    auto startIndex = cursor.snapshot();
    cursor.next();

    ExpressionSyntax *expr = tryParseSyntax<ExpressionSyntax>(cursor);
    if (expr == nullptr)
    {
        cursor.reset(startIndex);
        return nullptr;
    }

    if (!cursor.current()->isOperator() || cursor.current()->op() != ";"s)
    {
        cursor.reset(startIndex);
        return nullptr;
    }

    cursor.next();
    return new PrintStatementSyntax(startIndex, cursor.snapshot() - startIndex, expr, isPuts);
}

PrintStatementSyntax::PrintStatementSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *expr, bool isPuts)
    : StatementSyntax(startIndex, length), m_expr(expr), m_isPuts(isPuts)
{
}
PrintStatementSyntax::~PrintStatementSyntax()
{
}

ExpressionSyntax *PrintStatementSyntax::expr() const
{
    return this->m_expr;
}
bool PrintStatementSyntax::isPuts() const
{
    return this->m_isPuts;
}

bool PrintStatementSyntax::tryResolveTypes()
{
    auto worked = true;

    if (!this->expr()->tryResolveType()) worked = false;
    //TODO: verify condition type can be printed

    return worked;
}
void PrintStatementSyntax::assertTypesAreResolved() const
{
    throw std::logic_error("Not implemented"s);
}

void PrintStatementSyntax::emit(MethodBuilder&) const
{
    throw std::logic_error("Not implemented"s);
}

void PrintStatementSyntax::repr(std::stringstream &stream) const
{
    if (this->isPuts()) stream << "puts "s;
    else stream << "print "s;
    stream << this->expr() << ";"s;
}
