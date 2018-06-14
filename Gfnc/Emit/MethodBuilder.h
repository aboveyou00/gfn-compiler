#pragma once

namespace Gfn::Compiler::Emit
{
    class Opcode;
    class OpcodeTag;

    class MethodBuilder
    {
    public:
        MethodBuilder();
        ~MethodBuilder();

        OpcodeTag *createTag(std::string name);
        OpcodeTag *createAnonymousTag();
        void addTagToNextOpcode(OpcodeTag *tag);
        void addOpcode(Opcode *op);

        void finalize();
        bool isFinalized() const;

        const std::vector<Opcode*> &ops() const;

    private:
        std::vector<OpcodeTag*> m_pendingTags;
        std::vector<Opcode*> m_opcodes;
        int m_nextAnonymousIndex;
        bool m_isFinalized;

        void assertNotFinalized() const;
    };
}
