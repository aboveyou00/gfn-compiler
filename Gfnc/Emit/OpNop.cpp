#include "stdafx.h"
#include "Emit/OpNop.h"

OpNop::OpNop()
{
}
OpNop::~OpNop()
{
}

void OpNop::eval(EvalStack&) const
{
    ; //NOP
}
