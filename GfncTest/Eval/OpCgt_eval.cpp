#include "pch.h"
#include "Eval/EvalMacros.h"
#include "Emit/OpCgt.h"

TEST(OpCgt_eval, Simple_True) {
    PREPARE_STACK(5, 3);

    Emit::OpCgt op;
    op.eval(stack);

    EXPECT_STACK_RESULT(1);
}

TEST(OpCgt_eval, Simple_False) {
    PREPARE_STACK(3, 5);

    Emit::OpCgt op;
    op.eval(stack);

    EXPECT_STACK_RESULT(0);
}

TEST(OpCgt_eval, Identity) {
    PREPARE_STACK(5, 5);

    Emit::OpCgt op;
    op.eval(stack);

    EXPECT_STACK_RESULT(0);
}
