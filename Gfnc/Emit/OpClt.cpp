#include "stdafx.h"
#include "Emit/OpClt.h"
#include "Eval/EvalStack.h"

namespace Gfn::Compiler::Emit
{
    OpClt::OpClt()
    {
    }
    OpClt::~OpClt()
    {
    }

    void OpClt::eval(Eval::EvalStack &stack) const
    {
        int32_t lhs, rhs;
        std::tie(lhs, rhs) = stack.pop2();
        stack.push(lhs < rhs ? 1 : 0);
    }
}
