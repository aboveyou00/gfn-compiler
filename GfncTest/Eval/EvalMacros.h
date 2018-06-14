#pragma once
#include "Eval/EvalStack.h"

using namespace Gfn::Compiler;

template <typename TArg, typename... TArgs>
inline void pushAllToStack(Eval::EvalStack &stack, TArg arg, TArgs... args)
{
    pushAllToStack(stack, arg);
    pushAllToStack(stack, args...);
}
template <typename TArg>
inline void pushAllToStack(Eval::EvalStack &stack, TArg arg)
{
    stack.push(arg);
}
inline void pushAllToStack(Eval::EvalStack&)
{
}

#define PREPARE_STACK(...)\
    Eval::EvalStack stack;\
    pushAllToStack(stack, __VA_ARGS__);

#define EXPECT_STACK_RESULT(expectedResult)\
    EXPECT_TRUE(stack.size() == 1);\
    auto actualResult = stack.pop();\
    EXPECT_TRUE(actualResult == expectedResult);

#define EXPECT_EMPTY_STACK()\
    EXPECT_TRUE(stack.size() == 0);
