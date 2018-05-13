#include "stdafx.h"

#include "Parser/MultiplicativeExpressionSyntax.h"

#include "Parser/UnaryExpressionSyntax.h"
#include "Tokenizer/Token.h"
#include "Emit/OpMul.h"
#include "Emit/OpDiv.h"
#include "Emit/OpMod.h"

MultiplicativeExpressionSyntax::MultiplicativeExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *lhs, ExpressionSyntax *rhs, const std::string op)
    : BinaryExpressionSyntax(startIndex, length, lhs, rhs, op)
{
}
MultiplicativeExpressionSyntax::~MultiplicativeExpressionSyntax()
{
}

ExpressionSyntax *MultiplicativeExpressionSyntax::tryParse(Cursor<Token*> &cursor)
{
    ExpressionSyntax *expr = tryParseSyntax<UnaryExpressionSyntax>(cursor);
    if (expr == nullptr) return nullptr;

    while (true)
    {
        MultiplicativeExpressionSyntax *rhsExpr = tryParseRhs(cursor, expr);
        if (rhsExpr == nullptr) return expr;
        else expr = rhsExpr;
    }
}

void MultiplicativeExpressionSyntax::emit(std::vector<Opcode*> &ops) const
{
    this->lhs()->emit(ops);
    this->rhs()->emit(ops);

    if (this->op() == "*"s) ops.push_back(new OpMul());
    else if (this->op() == "/"s) ops.push_back(new OpDiv());
    else if (this->op() == "%"s) ops.push_back(new OpMod());
    else throw std::logic_error("Invalid multiplicative expression operation: " + this->op());
}

MultiplicativeExpressionSyntax *MultiplicativeExpressionSyntax::tryParseRhs(Cursor<Token*> &cursor, ExpressionSyntax *lhs)
{
    if (!cursor.current()->isOperator()) return nullptr;
    auto op = cursor.current()->op();
    if (op != "*" && op != "/" && op != "%") return nullptr;

    auto snapshot = cursor.snapshot();
    cursor.next();
    ExpressionSyntax *rhs = tryParseSyntax<UnaryExpressionSyntax>(cursor);
    if (rhs == nullptr)
    {
        cursor.reset(snapshot);
        return nullptr;
    }

    auto startIndex = lhs->startIndex();
    return new MultiplicativeExpressionSyntax(startIndex, cursor.snapshot() - startIndex, lhs, rhs, op);
}
