#include "pch.h"
#include "Eval/EvalMacros.h"
#include "Emit/OpMul.h"

TEST(OpMul_eval, Simple) {
    PREPARE_STACK(2, 3);

    OpMul op;
    op.eval(stack);

    EXPECT_STACK_RESULT(6);
}
