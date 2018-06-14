#include "stdafx.h"
#include "Emit/OpBranch.h"
#include "Eval/EvalContext.h"

namespace Gfn::Compiler::Emit
{
    OpBranch::OpBranch(OpcodeTag *tag)
        : BranchingOpcode(tag)
    {
    }
    OpBranch::~OpBranch()
    {
    }

    void OpBranch::eval(Eval::EvalContext &ctx) const
    {
        ctx.branchTo(this->tag());
    }
}
