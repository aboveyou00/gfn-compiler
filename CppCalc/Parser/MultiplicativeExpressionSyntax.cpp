#include "stdafx.h"

#include "Parser/MultiplicativeExpressionSyntax.h"

#include "Parser/UnaryExpressionSyntax.h"
#include "Tokenizer/Token.h"

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

MultiplicativeExpressionSyntax *MultiplicativeExpressionSyntax::tryParseRhs(Cursor<Token*> &cursor, ExpressionSyntax *lhs)
{
    if (!cursor.current()->isOperator()) return nullptr;
    auto op = cursor.current()->op();
    if (op != "*"s && op != "/"s && op != "%"s) return nullptr;

    auto snapshot = cursor.snapshot();
    cursor.next();
    ExpressionSyntax *rhs = tryParseSyntax<UnaryExpressionSyntax>(cursor);
    if (rhs == nullptr)
    {
        cursor.reset(snapshot);
        return nullptr;
    }

    auto startIndex = lhs->startIndex();
    return new MultiplicativeExpressionSyntax(startIndex, cursor.current()->startIndex() - startIndex, lhs, rhs, op);
}

MultiplicativeExpressionSyntax::MultiplicativeExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *lhs, ExpressionSyntax *rhs, const std::string op)
    : BinaryExpressionSyntax(startIndex, length, lhs, rhs, op)
{
}
MultiplicativeExpressionSyntax::~MultiplicativeExpressionSyntax()
{
}

std::string MultiplicativeExpressionSyntax::getOperatorMethodName() const
{
    if (this->op() == "*"s) return "__op_Multiply";
    else if (this->op() == "/"s) return "__op_Modulus";
    else if (this->op() == "%"s) return "__op_Division";
    else throw std::logic_error("Invalid multiplicative expression operation: "s + this->op());
}
