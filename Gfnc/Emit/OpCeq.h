#pragma once

#include "Emit/Opcode.h"

namespace Gfn::Compiler::Emit
{
    class OpCeq
        : public Opcode
    {
    public:
        OpCeq();
        ~OpCeq();

        virtual void eval(Eval::EvalStack &stack) const override;
    };
}
