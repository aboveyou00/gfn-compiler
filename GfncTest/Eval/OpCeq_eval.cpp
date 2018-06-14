#include "pch.h"
#include "Eval/EvalMacros.h"
#include "Emit/OpCeq.h"

TEST(OpCeq_eval, SimpleEquals) {
    PREPARE_STACK(3, 3);

    OpCeq op;
    op.eval(stack);

    EXPECT_STACK_RESULT(1);
}

TEST(OpCeq_eval, SimpleEqualsZero) {
    PREPARE_STACK(0, 0);

    OpCeq op;
    op.eval(stack);

    EXPECT_STACK_RESULT(1);
}

TEST(OpCeq_eval, SimpleNotEquals) {
    PREPARE_STACK(2, 3);

    OpCeq op;
    op.eval(stack);

    EXPECT_STACK_RESULT(0);
}
