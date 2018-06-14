#include "pch.h"
#include "Eval/EvalContext.h"
#include "Eval/EvalMacros.h"
#include "Emit/MethodBuilder.h"
#include "Emit/OpNop.h"
#include "Emit/OpBranch.h"

TEST(OpBranch_eval, Simple) {
    MethodBuilder mb;
    auto tag = mb.createAnonymousTag();
    mb.addTagToNextOpcode(tag);
    mb.addOpcode(new OpNop());
    auto op = new OpBranch(tag);
    mb.addOpcode(op);

    mb.finalize();
    auto &ops = mb.ops();

    EvalContext ctx(ops);
    ctx.nextInstructionIndex() = (uint32_t)ops.size();

    op->eval(ctx);

    EXPECT_TRUE(ctx.nextInstructionIndex() == 0);
    EXPECT_TRUE(ctx.stack().size() == 0);
}

TEST(OpBranch_eval, InvalidTag) {
    MethodBuilder mb;
    auto tag = mb.createAnonymousTag();
    mb.addOpcode(new OpNop());
    auto op = new OpBranch(tag);
    mb.addOpcode(op);

    mb.finalize();
    auto &ops = mb.ops();

    EvalContext ctx(ops);
    ctx.nextInstructionIndex() = (uint32_t)ops.size();

    EXPECT_THROW(op->eval(ctx), std::logic_error);
}
