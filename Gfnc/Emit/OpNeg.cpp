#include "stdafx.h"
#include "Emit/OpNeg.h"
#include "Eval/EvalStack.h"

namespace Gfn::Compiler::Emit
{
    OpNeg::OpNeg()
    {
    }
    OpNeg::~OpNeg()
    {
    }

    void OpNeg::eval(Eval::EvalStack &stack) const
    {
        int32_t inner = stack.pop();
        stack.push(-inner);
    }
}
