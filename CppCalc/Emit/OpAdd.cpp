#include "stdafx.h"
#include "Emit/OpAdd.h"

OpAdd::OpAdd()
{
}
OpAdd::~OpAdd()
{
}

void OpAdd::eval(EvalStack &stack) const
{
    int32_t lhs, rhs;
    std::tie(lhs, rhs) = stack.pop2();
    stack.push(lhs + rhs);
}
