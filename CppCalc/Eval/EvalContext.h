#pragma once

#include "Eval/EvalStack.h"

class Opcode;
class OpcodeTag;

class EvalContext
{
public:
    EvalContext(const std::vector<Opcode*> &opcodes);
    ~EvalContext();

    const std::vector<Opcode*> &ops() const;

    EvalStack &stack();
    uint32_t &nextInstructionIndex();

    void branchTo(OpcodeTag *tag);

private:
    const std::vector<Opcode*> m_opcodes;
    EvalStack m_stack;
    uint32_t m_nextInstructionIndex;
};
