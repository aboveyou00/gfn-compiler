#pragma once

#include "Emit/Opcode.h"

class OpClt
    : public Opcode
{
public:
    OpClt();
    ~OpClt();

    virtual void eval(EvalStack &stack) const override;
};
