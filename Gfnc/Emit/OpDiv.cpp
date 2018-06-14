#include "stdafx.h"
#include "Emit/OpDiv.h"
#include "Eval/EvalStack.h"

namespace Gfn::Compiler::Emit
{
    OpDiv::OpDiv()
    {
    }
    OpDiv::~OpDiv()
    {
    }

    void OpDiv::eval(Eval::EvalStack &stack) const
    {
        int32_t lhs, rhs;
        std::tie(lhs, rhs) = stack.pop2();
        stack.push(lhs / rhs);
    }
}
