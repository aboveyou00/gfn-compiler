#pragma once

#include "Emit/Opcode.h"

class OpNop
    : public Opcode
{
public:
    OpNop();
    ~OpNop();

    virtual void eval(EvalStack &stack) const override;
};
