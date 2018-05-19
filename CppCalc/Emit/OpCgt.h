#pragma once

#include "Emit/Opcode.h"

class OpCgt
    : public Opcode
{
public:
    OpCgt();
    ~OpCgt();

    virtual void eval(EvalStack &stack) const override;
};
