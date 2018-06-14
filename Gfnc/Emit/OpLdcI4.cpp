#include "stdafx.h"
#include "Emit/OpLdcI4.h"
#include "Eval/EvalStack.h"

namespace Gfn::Compiler::Emit
{
    OpLdcI4::OpLdcI4(int32_t val)
        : m_val(val)
    {
    }
    OpLdcI4::~OpLdcI4()
    {
    }

    int32_t OpLdcI4::value() const
    {
        return this->m_val;
    }

    void OpLdcI4::eval(Eval::EvalStack &stack) const
    {
        stack.push(this->m_val);
    }
}
