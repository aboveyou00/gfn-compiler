#include "pch.h"
#include "Emit/OpMacros.h"
#include "Emit/OpSub.h"

TEST(Emit_OpSub_eval, Simple) {
    PREPARE_STACK(3, 2);

    OpSub op;
    op.eval(stack);

    EXPECT_STACK_RESULT(1);
}
