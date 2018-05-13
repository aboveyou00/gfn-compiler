#include "stdafx.h"

#include "Parser/AdditiveExpressionSyntax.h"

#include "Parser/MultiplicativeExpressionSyntax.h"
#include "Tokenizer/Token.h"

AdditiveExpressionSyntax::AdditiveExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *lhs, ExpressionSyntax *rhs, const std::string op)
    : BinaryExpressionSyntax(startIndex, length, lhs, rhs, op)
{
}
AdditiveExpressionSyntax::~AdditiveExpressionSyntax()
{
}

ExpressionSyntax *AdditiveExpressionSyntax::tryParse(Cursor<Token*> &cursor)
{
    ExpressionSyntax *expr = tryParseSyntax<MultiplicativeExpressionSyntax>(cursor);
    if (expr == nullptr) return nullptr;

    while (true)
    {
        AdditiveExpressionSyntax *rhsExpr = tryParseRhs(cursor, expr);
        if (rhsExpr == nullptr) return expr;
        else expr = rhsExpr;
    }
}

void AdditiveExpressionSyntax::eval(std::stack<int32_t> &stack) const
{
    this->lhs()->eval(stack);
    this->rhs()->eval(stack);

    auto rightResult = stack.top();
    stack.pop();
    auto leftResult = stack.top();
    stack.pop();

    if (this->op() == "+"s)
    {
        stack.push(leftResult + rightResult);
    }
    else if (this->op() == "-"s)
    {
        stack.push(leftResult - rightResult);
    }
    else throw std::logic_error("Invalid additive expression operation: " + this->op());
}

AdditiveExpressionSyntax *AdditiveExpressionSyntax::tryParseRhs(Cursor<Token*> &cursor, ExpressionSyntax *lhs)
{
    if (!cursor.current()->isOperator()) return nullptr;
    auto op = cursor.current()->op();
    if (op != "+" && op != "-") return nullptr;

    auto snapshot = cursor.snapshot();
    cursor.next();
    ExpressionSyntax *rhs = tryParseSyntax<MultiplicativeExpressionSyntax>(cursor);
    if (rhs == nullptr)
    {
        cursor.reset(snapshot);
        return nullptr;
    }

    auto startIndex = lhs->startIndex();
    return new AdditiveExpressionSyntax(startIndex, cursor.snapshot() - startIndex, lhs, rhs, op);
}
