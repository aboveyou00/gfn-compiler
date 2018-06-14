#include "stdafx.h"
#include "Emit/OpNeg.h"

OpNeg::OpNeg()
{
}
OpNeg::~OpNeg()
{
}

void OpNeg::eval(EvalStack &stack) const
{
    int32_t inner = stack.pop();
    stack.push(-inner);
}
