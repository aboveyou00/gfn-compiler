#include "stdafx.h"
#include "Emit/OpNop.h"

namespace Gfn::Compiler::Emit
{
    OpNop::OpNop()
    {
    }
    OpNop::~OpNop()
    {
    }

    void OpNop::eval(Eval::EvalStack&) const
    {
        ; //NOP
    }
}
