#include "stdafx.h"
#include "Emit/OpAdd.h"
#include "Eval/EvalStack.h"

namespace Gfn::Compiler::Emit
{
    OpAdd::OpAdd()
    {
    }
    OpAdd::~OpAdd()
    {
    }

    void OpAdd::eval(Eval::EvalStack &stack) const
    {
        int32_t lhs, rhs;
        std::tie(lhs, rhs) = stack.pop2();
        stack.push(lhs + rhs);
    }
}
