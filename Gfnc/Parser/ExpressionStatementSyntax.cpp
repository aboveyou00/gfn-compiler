#include "stdafx.h"

#include "Parser/ExpressionStatementSyntax.h"

#include "Tokenizer/Token.h"
#include "Parser/ExpressionSyntax.h"
#include "Emit/MethodBuilder.h"

namespace Gfn::Compiler::Parser
{
    ExpressionStatementSyntax *ExpressionStatementSyntax::tryParse(Cursor<Tokenizer::Token*> &cursor)
    {
        auto startIndex = cursor.snapshot();

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
        return new ExpressionStatementSyntax(startIndex, cursor.snapshot() - startIndex, expr);
    }

    ExpressionStatementSyntax::ExpressionStatementSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *expr)
        : StatementSyntax(startIndex, length), m_expr(expr)
    {
    }
    ExpressionStatementSyntax::~ExpressionStatementSyntax()
    {
    }

    ExpressionSyntax *ExpressionStatementSyntax::expr() const
    {
        return this->m_expr;
    }

    bool ExpressionStatementSyntax::tryResolveTypes()
    {
        auto worked = true;

        if (!this->expr()->tryResolveType()) worked = false;

        return worked;
    }
    void ExpressionStatementSyntax::assertTypesAreResolved() const
    {
        throw std::logic_error("Not implemented"s);
    }

    void ExpressionStatementSyntax::emit(Runtime::MethodBuilder&) const
    {
        throw std::logic_error("Not implemented"s);
    }

    void ExpressionStatementSyntax::repr(std::stringstream &stream) const
    {
        stream << this->expr() << ";"s;
    }
}
