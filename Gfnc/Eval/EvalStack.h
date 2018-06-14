#pragma once

#include <stack>
#include <cstdint>
#include <tuple>

class EvalStack
{
public:
    EvalStack();
    ~EvalStack();

    int32_t peek() const;
    uint32_t size() const;
    int32_t pop();
    std::tuple<int32_t, int32_t> pop2();
    void push(int32_t val);

private:
    std::stack<int32_t> m_stack;
};
