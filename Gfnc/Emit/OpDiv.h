#pragma once

#include "Emit/Opcode.h"

namespace Gfn::Compiler::Emit
{
    class OpDiv
        : public Opcode
    {
    public:
        OpDiv();
        ~OpDiv();

        virtual void eval(Eval::EvalStack &stack) const override;
    };
}
