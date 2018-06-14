#pragma once

#include "Emit/Opcode.h"

class OpSub
    : public Opcode
{
public:
    OpSub();
    ~OpSub();

    virtual void eval(EvalStack &stack) const override;
};
