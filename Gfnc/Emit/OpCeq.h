#pragma once

#include "Emit/Opcode.h"

class OpCeq
    : public Opcode
{
public:
    OpCeq();
    ~OpCeq();

    virtual void eval(EvalStack &stack) const override;
};
