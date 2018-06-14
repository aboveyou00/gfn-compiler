#include "stdafx.h"
#include "Emit/OpMul.h"
#include "Eval/EvalStack.h"

namespace Gfn::Compiler::Emit
{
    OpMul::OpMul()
    {
    }
    OpMul::~OpMul()
    {
    }

    void OpMul::eval(Eval::EvalStack &stack) const
    {
        int32_t lhs, rhs;
        std::tie(lhs, rhs) = stack.pop2();
        stack.push(lhs * rhs);
    }
}
