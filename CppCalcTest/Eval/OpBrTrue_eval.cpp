#include "pch.h"
#include "Eval/EvalContext.h"
#include "Eval/EvalMacros.h"
#include "Emit/MethodBuilder.h"
#include "Emit/OpNop.h"
#include "Emit/OpBrTrue.h"

TEST(OpBrTrue_eval, Simple_True) {
    MethodBuilder mb;
    auto tag = mb.createAnonymousTag();
    mb.addTagToNextOpcode(tag);
    mb.addOpcode(new OpNop());
    auto op = new OpBrTrue(tag);
    mb.addOpcode(op);

    mb.finalize();
    auto &ops = mb.ops();

    EvalContext ctx(ops);
    ctx.nextInstructionIndex() = (uint32_t)ops.size();
    pushAllToStack(ctx.stack(), 1);

    op->eval(ctx);

    EXPECT_TRUE(ctx.nextInstructionIndex() == 0);
    EXPECT_TRUE(ctx.stack().size() == 0);
}

TEST(OpBrTrue_eval, Simple_False) {
    MethodBuilder mb;
    auto tag = mb.createAnonymousTag();
    mb.addTagToNextOpcode(tag);
    mb.addOpcode(new OpNop());
    auto op = new OpBrTrue(tag);
    mb.addOpcode(op);

    mb.finalize();
    auto &ops = mb.ops();

    EvalContext ctx(ops);
    ctx.nextInstructionIndex() = (uint32_t)ops.size();
    pushAllToStack(ctx.stack(), 0);

    op->eval(ctx);

    EXPECT_TRUE(ctx.nextInstructionIndex() == ops.size());
    EXPECT_TRUE(ctx.stack().size() == 0);
}

TEST(OpBrTrue_eval, InvalidTag) {
    MethodBuilder mb;
    auto tag = mb.createAnonymousTag();
    mb.addOpcode(new OpNop());
    auto op = new OpBrTrue(tag);
    mb.addOpcode(op);

    mb.finalize();
    auto &ops = mb.ops();

    EvalContext ctx(ops);
    ctx.nextInstructionIndex() = (uint32_t)ops.size();
    pushAllToStack(ctx.stack(), 1);

    EXPECT_THROW(op->eval(ctx), std::logic_error);
}

TEST(OpBrTrue_eval, InvalidStack) {
    MethodBuilder mb;
    auto tag = mb.createAnonymousTag();
    mb.addTagToNextOpcode(tag);
    mb.addOpcode(new OpNop());
    auto op = new OpBrTrue(tag);
    mb.addOpcode(op);

    mb.finalize();
    auto &ops = mb.ops();

    EvalContext ctx(ops);
    ctx.nextInstructionIndex() = (uint32_t)ops.size();

    EXPECT_THROW(op->eval(ctx), std::logic_error);
}
