#include "pch.h"
#include "Eval/EvalMacros.h"
#include "Emit/OpNeg.h"

TEST(OpNeg_eval, Simple) {
    PREPARE_STACK(13);

    OpNeg op;
    op.eval(stack);

    EXPECT_STACK_RESULT(-13);
}
