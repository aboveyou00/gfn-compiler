#include "pch.h"
#include "Eval/EvalMacros.h"
#include "Emit/OpAdd.h"

TEST(OpAdd_eval, Simple) {
    PREPARE_STACK(2, 3);

    Emit::OpAdd op;
    op.eval(stack);

    EXPECT_STACK_RESULT(5);
}
