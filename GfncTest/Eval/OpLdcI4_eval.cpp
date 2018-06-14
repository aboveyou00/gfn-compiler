#include "pch.h"
#include "Eval/EvalMacros.h"
#include "Emit/OpLdcI4.h"

TEST(OpLdcI4_eval, Simple) {
    PREPARE_STACK();

    OpLdcI4 op(42);
    op.eval(stack);

    EXPECT_STACK_RESULT(42);
}
