#include "stdafx.h"
#include "Emit/OpDiv.h"

OpDiv::OpDiv()
{
}
OpDiv::~OpDiv()
{
}

void OpDiv::eval(EvalStack &stack) const
{
    int32_t lhs, rhs;
    std::tie(lhs, rhs) = stack.pop2();
    stack.push(lhs / rhs);
}
