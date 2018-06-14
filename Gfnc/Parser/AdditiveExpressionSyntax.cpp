#include "stdafx.h"

#include "Parser/AdditiveExpressionSyntax.h"

#include "Parser/MultiplicativeExpressionSyntax.h"
#include "Tokenizer/Token.h"

namespace Gfn::Compiler::Parser
{
    ExpressionSyntax *AdditiveExpressionSyntax::tryParse(Cursor<Tokenizer::Token*> &cursor)
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

    AdditiveExpressionSyntax *AdditiveExpressionSyntax::tryParseRhs(Cursor<Tokenizer::Token*> &cursor, ExpressionSyntax *lhs)
    {
        if (!cursor.current()->isOperator()) return nullptr;
        auto op = cursor.current()->op();
        if (op != "+"s && op != "-"s) return nullptr;

        auto snapshot = cursor.snapshot();
        cursor.next();
        ExpressionSyntax *rhs = tryParseSyntax<MultiplicativeExpressionSyntax>(cursor);
        if (rhs == nullptr)
        {
            cursor.reset(snapshot);
            return nullptr;
        }

        auto startIndex = lhs->startIndex();
        return new AdditiveExpressionSyntax(startIndex, cursor.current()->startIndex() - startIndex, lhs, rhs, op);
    }

    AdditiveExpressionSyntax::AdditiveExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *lhs, ExpressionSyntax *rhs, const std::string op)
        : BinaryExpressionSyntax(startIndex, length, lhs, rhs, op)
    {
    }
    AdditiveExpressionSyntax::~AdditiveExpressionSyntax()
    {
    }

    std::string AdditiveExpressionSyntax::getOperatorMethodName() const
    {
        if (this->op() == "+"s) return "__op_Addition";
        else if (this->op() == "-"s) return "__op_Subtraction";
        else throw std::logic_error("Invalid additive expression operation: "s + this->op());
    }
}
