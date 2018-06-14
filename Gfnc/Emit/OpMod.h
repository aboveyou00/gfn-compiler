#pragma once

#include "Emit/Opcode.h"

namespace Gfn::Compiler::Emit
{
    class OpMod
        : public Opcode
    {
    public:
        OpMod();
        ~OpMod();

        virtual void eval(Eval::EvalStack &stack) const override;
    };
}
