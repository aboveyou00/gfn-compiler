#pragma once

#include "Eval/EvalStack.h"

namespace Gfn::Compiler::Emit
{
    class Opcode;
    class OpcodeTag;
}

namespace Gfn::Compiler::Eval
{
    class EvalContext
    {
    public:
        EvalContext(const std::vector<Emit::Opcode*> &opcodes);
        ~EvalContext();

        const std::vector<Emit::Opcode*> &ops() const;

        EvalStack &stack();
        uint32_t &nextInstructionIndex();

        void branchTo(Emit::OpcodeTag *tag);

    private:
        const std::vector<Emit::Opcode*> m_opcodes;
        EvalStack m_stack;
        uint32_t m_nextInstructionIndex;
    };
}
