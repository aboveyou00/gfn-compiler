#include "pch.h"
#include "Eval/EvalMacros.h"
#include "Emit/OpClt.h"

TEST(OpClt_eval, Simple_True) {
    PREPARE_STACK(3, 5);

    OpClt op;
    op.eval(stack);

    EXPECT_STACK_RESULT(1);
}

TEST(OpClt_eval, Simple_False) {
    PREPARE_STACK(5, 3);

    OpClt op;
    op.eval(stack);

    EXPECT_STACK_RESULT(0);
}

TEST(OpClt_eval, Identity) {
    PREPARE_STACK(5, 5);

    OpClt op;
    op.eval(stack);

    EXPECT_STACK_RESULT(0);
}
