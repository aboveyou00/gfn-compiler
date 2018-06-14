#pragma once

#include "Emit/Opcode.h"

namespace Gfn::Compiler::Emit
{
    class OpAdd
        : public Opcode
    {
    public:
        OpAdd();
        ~OpAdd();

        virtual void eval(Eval::EvalStack &stack) const override;
    };
}
