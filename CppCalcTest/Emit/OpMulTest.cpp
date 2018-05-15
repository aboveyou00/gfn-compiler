#include "pch.h"
#include "Emit/OpMacros.h"
#include "Emit/OpMul.h"

TEST(Emit_OpMul_eval, Simple) {
    PREPARE_STACK(2, 3);

    OpMul op;
    op.eval(stack);

    EXPECT_STACK_RESULT(6);
}
