#include "pch.h"
#include "Eval/EvalMacros.h"
#include "Emit/OpMod.h"

TEST(OpMod_eval, Simple) {
    PREPARE_STACK(11, 6);

    OpMod op;
    op.eval(stack);

    EXPECT_STACK_RESULT(5);
}
