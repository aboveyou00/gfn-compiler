#include "stdafx.h"
#include "Emit/OpBrFalse.h"
#include "Eval/EvalContext.h"

namespace Gfn::Compiler::Emit
{
    OpBrFalse::OpBrFalse(OpcodeTag *tag)
        : BranchingOpcode(tag)
    {
    }
    OpBrFalse::~OpBrFalse()
    {
    }

    void OpBrFalse::eval(Eval::EvalContext &ctx) const
    {
        auto &stack = ctx.stack();
        if (stack.size() == 0) throw std::logic_error("Cannot evaluate OpBrFalse: there are no values on the stack!"s);
        auto top = stack.pop();
        if (top == 0) ctx.branchTo(this->tag());
    }
}
