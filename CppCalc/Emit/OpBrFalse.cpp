#include "stdafx.h"
#include "Emit/OpBrFalse.h"

OpBrFalse::OpBrFalse(OpcodeTag *tag)
    : BranchingOpcode(tag)
{
}
OpBrFalse::~OpBrFalse()
{
}

void OpBrFalse::eval(EvalContext &ctx) const
{
    auto top = ctx.stack().pop();
    if (top == 0) ctx.branchTo(this->tag());
}
