#pragma once

#include "Emit/Opcode.h"

namespace Gfn::Compiler::Emit
{
    class OpSub
        : public Opcode
    {
    public:
        OpSub();
        ~OpSub();

        virtual void eval(Eval::EvalStack &stack) const override;
    };
}
