#include "pch.h"
#include "Eval/EvalMacros.h"
#include "Emit/OpNop.h"

TEST(OpNop_eval, EmptyStack) {
    PREPARE_STACK();

    OpNop op;
    op.eval(stack);

    EXPECT_EMPTY_STACK();
}

TEST(OpNop_eval, UnmodifiedStack) {
    PREPARE_STACK(25);

    OpNop op;
    op.eval(stack);

    EXPECT_STACK_RESULT(25);
}
