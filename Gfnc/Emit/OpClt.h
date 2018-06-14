#pragma once

#include "Emit/Opcode.h"

namespace Gfn::Compiler::Emit
{
    class OpClt
        : public Opcode
    {
    public:
        OpClt();
        ~OpClt();

        virtual void eval(Eval::EvalStack &stack) const override;
    };
}
