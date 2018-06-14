#pragma once

#include "Emit/Opcode.h"

namespace Gfn::Compiler::Emit
{
    class BranchingOpcode
        : public Opcode
    {
    public:
        BranchingOpcode(OpcodeTag *tag);
        ~BranchingOpcode();

        OpcodeTag *tag() const;

        virtual void eval(Eval::EvalContext &ctx) const = 0;
        virtual void eval(Eval::EvalStack &stack) const override;

    private:
        OpcodeTag * m_tag;
    };
}
