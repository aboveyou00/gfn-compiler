#include "pch.h"
#include "Eval/EvalMacros.h"
#include "Emit/OpDiv.h"

TEST(OpDiv_eval, Simple) {
    PREPARE_STACK(20, 5);

    OpDiv op;
    op.eval(stack);

    EXPECT_STACK_RESULT(4);
}

TEST(OpDiv_eval, IntegerDivision) {
    PREPARE_STACK(3, 2);

    OpDiv op;
    op.eval(stack);

    EXPECT_STACK_RESULT(1);
}
