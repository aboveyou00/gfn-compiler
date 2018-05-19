#include "stdafx.h"

#include "Parser/RelationalExpressionSyntax.h"

#include "Parser/AdditiveExpressionSyntax.h"
#include "Tokenizer/Token.h"
#include "Emit/OpClt.h"
#include "Emit/OpCgt.h"
#include "Emit/OpCeq.h"
#include "Emit/OpLdcI4.h"

RelationalExpressionSyntax::RelationalExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *lhs, ExpressionSyntax *rhs, const std::string op)
    : BinaryExpressionSyntax(startIndex, length, lhs, rhs, op)
{
}
RelationalExpressionSyntax::~RelationalExpressionSyntax()
{
}

ExpressionSyntax *RelationalExpressionSyntax::tryParse(Cursor<Token*> &cursor)
{
    ExpressionSyntax *expr = tryParseSyntax<AdditiveExpressionSyntax>(cursor);
    if (expr == nullptr) return nullptr;

    while (true)
    {
        RelationalExpressionSyntax *rhsExpr = tryParseRhs(cursor, expr);
        if (rhsExpr == nullptr) return expr;
        else expr = rhsExpr;
    }
}

void RelationalExpressionSyntax::emit(std::vector<Opcode*> &ops) const
{
    this->lhs()->emit(ops);
    this->rhs()->emit(ops);

    if (this->op() == "<"s) ops.push_back(new OpClt());
    else if (this->op() == ">"s) ops.push_back(new OpCgt());
    else if (this->op() == "<="s)
    {
        ops.push_back(new OpCgt());
        ops.push_back(new OpLdcI4(0));
        ops.push_back(new OpCeq());
    }
    else if (this->op() == ">="s)
    {
        ops.push_back(new OpClt());
        ops.push_back(new OpLdcI4(0));
        ops.push_back(new OpCeq());
    }
    else throw std::logic_error("Invalid relational expression operation: "s + this->op());
}

RelationalExpressionSyntax *RelationalExpressionSyntax::tryParseRhs(Cursor<Token*> &cursor, ExpressionSyntax *lhs)
{
    if (!cursor.current()->isOperator()) return nullptr;
    auto op = cursor.current()->op();
    if (op != "<"s && op != ">"s && op != "<="s && op != ">="s) return nullptr;

    auto snapshot = cursor.snapshot();
    cursor.next();
    ExpressionSyntax *rhs = tryParseSyntax<AdditiveExpressionSyntax>(cursor);
    if (rhs == nullptr)
    {
        cursor.reset(snapshot);
        return nullptr;
    }

    auto startIndex = lhs->startIndex();
    return new RelationalExpressionSyntax(startIndex, cursor.current()->startIndex() - startIndex, lhs, rhs, op);
}
