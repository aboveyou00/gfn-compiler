#pragma once

#include "Emit/BranchingOpcode.h"

namespace Gfn::Compiler::Emit
{
    class OpBrTrue
        : public BranchingOpcode
    {
    public:
        OpBrTrue(OpcodeTag *tag);
        ~OpBrTrue();

        virtual void eval(Eval::EvalContext &ctx) const override;
    };
}
