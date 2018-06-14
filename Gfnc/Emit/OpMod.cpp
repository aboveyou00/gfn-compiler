#include "stdafx.h"
#include "Emit/OpMod.h"
#include "Eval/EvalStack.h"

namespace Gfn::Compiler::Emit
{
    OpMod::OpMod()
    {
    }
    OpMod::~OpMod()
    {
    }

    void OpMod::eval(Eval::EvalStack &stack) const
    {
        int32_t lhs, rhs;
        std::tie(lhs, rhs) = stack.pop2();
        stack.push(lhs % rhs);
    }
}
