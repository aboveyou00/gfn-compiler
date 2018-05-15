#include "pch.h"
#include "Emit/OpMacros.h"
#include "Emit/OpLdcI4.h"

TEST(Emit_OpLdcI4_eval, Simple) {
    PREPARE_STACK();

    OpLdcI4 op(42);
    op.eval(stack);

    EXPECT_STACK_RESULT(42);
}
