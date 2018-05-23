#include "stdafx.h"

#include "Parser/UnaryExpressionSyntax.h"

#include "Parser/PrimaryExpressionSyntax.h"
#include "Tokenizer/Token.h"
#include "Emit/OpLdcI4.h"

#include "Runtime/RuntimeType.h"
#include "Runtime/MethodGroup.h"
#include "Runtime/MethodOverload.h"

ExpressionSyntax *UnaryExpressionSyntax::tryParse(Cursor<Token*> &cursor)
{
    if (cursor.current()->isOperator())
    {
        auto op = cursor.current()->op();
        if (op == "+"s || op == "-"s || op == "!"s)
        {
            auto startIndex = cursor.current()->startIndex();
            auto snapshot = cursor.snapshot();
            cursor.next();
            ExpressionSyntax *rhs = tryParseSyntax<UnaryExpressionSyntax>(cursor);
            if (rhs == nullptr) cursor.reset(snapshot);
            else return new UnaryExpressionSyntax(startIndex, cursor.current()->startIndex() - startIndex, rhs, op);
        }
    }

    return tryParseSyntax<PrimaryExpressionSyntax>(cursor);
}

UnaryExpressionSyntax::UnaryExpressionSyntax(uint32_t startIndex, uint32_t length, ExpressionSyntax *expr, const std::string op)
    : ExpressionSyntax(startIndex, length), m_expr(expr), m_op(op), m_selectedOperatorOverload(nullptr)
{
}
UnaryExpressionSyntax::~UnaryExpressionSyntax()
{
    SafeDelete(this->m_expr);
}

ExpressionSyntax *UnaryExpressionSyntax::expr() const
{
    return this->m_expr;
}
const std::string UnaryExpressionSyntax::op() const
{
    return this->m_op;
}

bool UnaryExpressionSyntax::tryResolveType()
{
    if (this->m_resolvedType != nullptr) return true;

    //Note: this top part is to handle the special case of having the minimum value for uint32_t
    if (this->isNegativeNumericLimit())
    {
        this->m_resolvedType = RuntimeType::int32();
        return true;
    }

    if (!this->expr()->tryResolveType()) return false;

    auto exprType = this->expr()->resolvedType();

    auto operatorMethodName = this->getOperatorMethodName();
    auto methods = exprType->getStaticMethods(operatorMethodName);
    if (methods != nullptr)
    {
        this->m_selectedOperatorOverload = methods->findOverload({ exprType });
    }

    if (this->m_selectedOperatorOverload == nullptr) return false;
    this->m_resolvedType = this->m_selectedOperatorOverload->returnType();
    return true;
}

void UnaryExpressionSyntax::emit(std::vector<Opcode*> &ops) const
{
    this->assertTypeIsResolved();

    //Note: this top part is to handle the special case of having the minimum value for uint32_t
    if (this->isNegativeNumericLimit())
    {
        ops.push_back(new OpLdcI4(std::numeric_limits<int32_t>::min()));
        return;
    }

    this->expr()->emit(ops);

    this->m_selectedOperatorOverload->emitInvoke(ops);
}

void UnaryExpressionSyntax::repr(std::stringstream &stream) const
{
    stream << this->op() << this->expr();
}

std::string UnaryExpressionSyntax::getOperatorMethodName() const
{
    if (this->op() == "+"s) return "__op_UnaryPlus"s;
    else if (this->op() == "-"s) return "__op_UnaryNegation"s;
    else if (this->op() == "!"s) return "__op_LogicalNot"s;
    else throw std::logic_error("Invalid unary expression operation: "s + this->op());
}

bool UnaryExpressionSyntax::isNegativeNumericLimit() const
{
    if (this->op() != "-"s) return false;
    auto primaryExpr = dynamic_cast<PrimaryExpressionSyntax*>(this->expr());
    if (primaryExpr == nullptr) return false;
    if (primaryExpr->type() != PrimaryExpressionType::IntegerLiteral || primaryExpr->intLiteralValue() != (uint64_t)-(int64_t)std::numeric_limits<int32_t>::min()) return false;
    if (primaryExpr->startIndex() != this->startIndex() + 1) return false;
    return true;
}
