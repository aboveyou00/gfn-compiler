#include "stdafx.h"
#include "Emit/OpSub.h"
#include "Eval/EvalStack.h"

namespace Gfn::Compiler::Emit
{
    OpSub::OpSub()
    {
    }
    OpSub::~OpSub()
    {
    }

    void OpSub::eval(Eval::EvalStack &stack) const
    {
        int32_t lhs, rhs;
        std::tie(lhs, rhs) = stack.pop2();
        stack.push(lhs - rhs);
    }
}
