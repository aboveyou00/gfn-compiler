#include "stdafx.h"
#include "Parser/StatementSyntax.h"
#include "Parser/IfStatementSyntax.h"
#include "Parser/PrintStatementSyntax.h"
#include "Parser/ExpressionStatementSyntax.h"

namespace Gfn::Compiler::Parser
{
    StatementSyntax *StatementSyntax::tryParse(Cursor<Tokenizer::Token*> &cursor)
    {
        StatementSyntax *expr;

        expr = IfStatementSyntax::tryParse(cursor);
        if (expr != nullptr) return expr;
        expr = PrintStatementSyntax::tryParse(cursor);
        if (expr != nullptr) return expr;
        expr = ExpressionStatementSyntax::tryParse(cursor);
        if (expr != nullptr) return expr;

        return nullptr;
    }

    StatementSyntax::StatementSyntax(uint32_t startIndex, uint32_t length)
        : Syntax(startIndex, length)
    {
    }
    StatementSyntax::~StatementSyntax()
    {
    }
}
