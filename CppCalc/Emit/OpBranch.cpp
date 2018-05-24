#include "stdafx.h"
#include "Emit/OpBranch.h"

OpBranch::OpBranch(OpcodeTag *tag)
    : BranchingOpcode(tag)
{
}
OpBranch::~OpBranch()
{
}

void OpBranch::eval(EvalContext &ctx) const
{
    ctx.branchTo(this->tag());
}
