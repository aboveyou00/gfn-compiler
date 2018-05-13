#include "stdafx.h"

#include "Parser/MultiplicativeExpressionSyntax.h"

#include "Parser/UnaryExpressionSyntax.h"
#include "Tokenizer/Token.h"

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

void MultiplicativeExpressionSyntax::eval(std::stack<int32_t> &stack) const
{
    this->lhs()->eval(stack);
    this->rhs()->eval(stack);

    auto rightResult = stack.top();
    stack.pop();
    auto leftResult = stack.top();
    stack.pop();

    if (this->op() == "*"s)
    {
        stack.push(leftResult * rightResult);
    }
    else if (this->op() == "/"s)
    {
        stack.push(leftResult / rightResult);
    }
    else if (this->op() == "%"s)
    {
        stack.push(leftResult % rightResult);
    }
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
