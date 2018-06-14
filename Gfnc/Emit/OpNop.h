#pragma once

#include "Emit/Opcode.h"

namespace Gfn::Compiler::Emit
{
    class OpNop
        : public Opcode
    {
    public:
        OpNop();
        ~OpNop();

        virtual void eval(Eval::EvalStack &stack) const override;
    };
}
