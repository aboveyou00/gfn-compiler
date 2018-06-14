#include "stdafx.h"
#include "Emit/OpBrTrue.h"
#include "Eval/EvalContext.h"

namespace Gfn::Compiler::Emit
{
    OpBrTrue::OpBrTrue(OpcodeTag *tag)
        : BranchingOpcode(tag)
    {
    }
    OpBrTrue::~OpBrTrue()
    {
    }

    void OpBrTrue::eval(Eval::EvalContext &ctx) const
    {
        auto &stack = ctx.stack();
        if (stack.size() == 0) throw std::logic_error("Cannot evaluate OpBrTrue: there are no values on the stack!"s);
        auto top = stack.pop();
        if (top != 0) ctx.branchTo(this->tag());
    }
}
