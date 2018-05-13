#include "stdafx.h"
#include "Emit/OpMul.h"

OpMul::OpMul()
{
}
OpMul::~OpMul()
{
}

void OpMul::eval(EvalStack &stack) const
{
    int32_t lhs, rhs;
    std::tie(lhs, rhs) = stack.pop2();
    stack.push(lhs * rhs);
}
