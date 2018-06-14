#include "pch.h"
#include "Eval/EvalMacros.h"
#include "Emit/OpSub.h"

TEST(OpSub_eval, Simple) {
    PREPARE_STACK(3, 2);

    Emit::OpSub op;
    op.eval(stack);

    EXPECT_STACK_RESULT(1);
}
