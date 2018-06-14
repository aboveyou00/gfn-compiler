#pragma once

#include "Emit/Opcode.h"

namespace Gfn::Compiler::Emit
{
    class OpCgt
        : public Opcode
    {
    public:
        OpCgt();
        ~OpCgt();

        virtual void eval(Eval::EvalStack &stack) const override;
    };
}
