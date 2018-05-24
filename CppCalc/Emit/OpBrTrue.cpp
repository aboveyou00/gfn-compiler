#include "stdafx.h"
#include "Emit/OpBrTrue.h"

OpBrTrue::OpBrTrue(OpcodeTag *tag)
    : BranchingOpcode(tag)
{
}
OpBrTrue::~OpBrTrue()
{
}

void OpBrTrue::eval(EvalContext &ctx) const
{
    auto top = ctx.stack().pop();
    if (top != 0) ctx.branchTo(this->tag());
}
