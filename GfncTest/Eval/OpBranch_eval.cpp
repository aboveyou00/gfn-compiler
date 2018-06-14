#include "pch.h"
#include "Eval/EvalContext.h"
#include "Eval/EvalMacros.h"
#include "Emit/MethodBuilder.h"
#include "Emit/OpNop.h"
#include "Emit/OpBranch.h"

TEST(OpBranch_eval, Simple) {
    Emit::MethodBuilder mb;
    auto tag = mb.createAnonymousTag();
    mb.addTagToNextOpcode(tag);
    mb.addOpcode(new Emit::OpNop());
    auto op = new Emit::OpBranch(tag);
    mb.addOpcode(op);

    mb.finalize();
    auto &ops = mb.ops();

    Eval::EvalContext ctx(ops);
    ctx.nextInstructionIndex() = (uint32_t)ops.size();

    op->eval(ctx);

    EXPECT_TRUE(ctx.nextInstructionIndex() == 0);
    EXPECT_TRUE(ctx.stack().size() == 0);
}

TEST(OpBranch_eval, InvalidTag) {
    Emit::MethodBuilder mb;
    auto tag = mb.createAnonymousTag();
    mb.addOpcode(new Emit::OpNop());
    auto op = new Emit::OpBranch(tag);
    mb.addOpcode(op);

    mb.finalize();
    auto &ops = mb.ops();

    Eval::EvalContext ctx(ops);
    ctx.nextInstructionIndex() = (uint32_t)ops.size();

    EXPECT_THROW(op->eval(ctx), std::logic_error);
}
