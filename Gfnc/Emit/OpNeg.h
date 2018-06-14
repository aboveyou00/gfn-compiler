#pragma once

#include "Emit/Opcode.h"

namespace Gfn::Compiler::Emit
{
    class OpNeg
        : public Opcode
    {
    public:
        OpNeg();
        ~OpNeg();

        virtual void eval(Eval::EvalStack &stack) const override;
    };
}
