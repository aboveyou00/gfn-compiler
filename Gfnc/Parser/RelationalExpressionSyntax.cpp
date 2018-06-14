#include "stdafx.h"

#include "Parser/RelationalExpressionSyntax.h"

#include "Parser/AdditiveExpressionSyntax.h"
#include "Tokenizer/Token.h"

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

RelationalExpressionSyntax::RelationalExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *lhs, ExpressionSyntax *rhs, const std::string op)
    : BinaryExpressionSyntax(startIndex, length, lhs, rhs, op)
{
}
RelationalExpressionSyntax::~RelationalExpressionSyntax()
{
}

std::string RelationalExpressionSyntax::getOperatorMethodName() const
{
    if (this->op() == "<"s) return "__op_LessThan";
    else if (this->op() == ">"s) return "__op_GreaterThan";
    else if (this->op() == "<="s) return "__op_LessThanOrEqual";
    else if (this->op() == ">="s) return "__op_GreaterThanOrEqual";
    else throw std::logic_error("Invalid relational expression operation: "s + this->op());
}
