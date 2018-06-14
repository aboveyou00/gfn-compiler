#include "stdafx.h"
#include "Emit/OpCeq.h"
#include "Eval/EvalStack.h"

namespace Gfn::Compiler::Emit
{
    OpCeq::OpCeq()
    {
    }
    OpCeq::~OpCeq()
    {
    }

    void OpCeq::eval(Eval::EvalStack &stack) const
    {
        int32_t lhs, rhs;
        std::tie(lhs, rhs) = stack.pop2();
        stack.push(lhs == rhs ? 1 : 0);
    }
}
