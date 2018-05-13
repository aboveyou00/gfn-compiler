#pragma once

#include "Emit/Opcode.h"

class OpAdd
    : public Opcode
{
public:
    OpAdd();
    ~OpAdd();

    virtual void eval(EvalStack &stack) const override;
};
