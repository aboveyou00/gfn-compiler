#include "pch.h"
#include "Emit/OpMacros.h"
#include "Emit/OpNeg.h"

TEST(Emit_OpNeg_eval, Simple) {
    PREPARE_STACK(13);

    OpNeg op;
    op.eval(stack);

    EXPECT_STACK_RESULT(-13);
}
