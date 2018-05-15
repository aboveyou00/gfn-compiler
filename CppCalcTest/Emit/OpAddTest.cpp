#include "pch.h"
#include "Emit/OpMacros.h"
#include "Emit/OpAdd.h"

TEST(Emit_OpAdd_eval, Simple) {
    PREPARE_STACK(2, 3);

    OpAdd op;
    op.eval(stack);

    EXPECT_STACK_RESULT(5);
}
