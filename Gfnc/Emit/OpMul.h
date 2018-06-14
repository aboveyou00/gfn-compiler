#pragma once

#include "Emit/Opcode.h"

namespace Gfn::Compiler::Emit
{
    class OpMul
        : public Opcode
    {
    public:
        OpMul();
        ~OpMul();

        virtual void eval(Eval::EvalStack &stack) const override;
    };
}
