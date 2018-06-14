#include "stdafx.h"
#include "Emit/OpSub.h"

OpSub::OpSub()
{
}
OpSub::~OpSub()
{
}

void OpSub::eval(EvalStack &stack) const
{
    int32_t lhs, rhs;
    std::tie(lhs, rhs) = stack.pop2();
    stack.push(lhs - rhs);
}
