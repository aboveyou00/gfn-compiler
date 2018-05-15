#include "pch.h"
#include "Emit/OpMacros.h"
#include "Emit/OpMod.h"

TEST(Emit_OpMod_eval, Simple) {
    PREPARE_STACK(11, 6);

    OpMod op;
    op.eval(stack);

    EXPECT_STACK_RESULT(5);
}
