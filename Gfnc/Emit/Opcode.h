#pragma once

namespace Gfn::Compiler::Eval
{
    class EvalContext;
    class EvalStack;
}

namespace Gfn::Compiler::Emit
{
    class OpcodeTag;

    class Opcode
    {
    public:
        Opcode();
        ~Opcode();

        const std::vector<OpcodeTag*> &tags() const;
        bool hasTag(OpcodeTag *tag) const;

        void addTag(OpcodeTag *tag);

        virtual void eval(Eval::EvalContext &ctx) const;
        virtual void eval(Eval::EvalStack &stack) const = 0;

    private:
        std::vector<OpcodeTag*> m_tags;
    };
}
