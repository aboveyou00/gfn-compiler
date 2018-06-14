#include "stdafx.h"
#include "Emit/OpCgt.h"

OpCgt::OpCgt()
{
}
OpCgt::~OpCgt()
{
}

void OpCgt::eval(EvalStack &stack) const
{
    int32_t lhs, rhs;
    std::tie(lhs, rhs) = stack.pop2();
    stack.push(lhs > rhs ? 1 : 0);
}
